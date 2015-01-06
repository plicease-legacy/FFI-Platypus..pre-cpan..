    if(items-(EXTRA_ARGS) != self->ffi_cif.nargs)
      croak("wrong number of arguments (expected %d, got %d)", self->ffi_cif.nargs, items-(EXTRA_ARGS) );

    buffer_size = sizeof(ffi_pl_argument) * self->ffi_cif.nargs * 2 + sizeof(ffi_pl_arguments);
#ifdef HAVE_ALLOCA
    buffer = alloca(buffer_size);
#else
    Newx(buffer, buffer_size, char);
#endif
    arguments = (ffi_pl_arguments*) buffer;

    arguments->count = self->ffi_cif.nargs;

    for(i=0; i<items-(EXTRA_ARGS); i++)
    {
      ((void**)&arguments->slot[arguments->count])[i] = &arguments->slot[i];

      arg = ST(i+(EXTRA_ARGS));
      if(self->argument_types[i]->platypus_type == FFI_PL_FFI)
      {
        switch(self->argument_types[i]->ffi_type->type)
        {
          case FFI_TYPE_UINT8:
            ffi_pl_arguments_set_uint8(arguments, i, SvUV(arg));
            break;
          case FFI_TYPE_SINT8:
            ffi_pl_arguments_set_sint8(arguments, i, SvIV(arg));
            break;
          case FFI_TYPE_UINT16:
            ffi_pl_arguments_set_uint16(arguments, i, SvUV(arg));
            break;
          case FFI_TYPE_SINT16:
            ffi_pl_arguments_set_sint16(arguments, i, SvIV(arg));
            break;
          case FFI_TYPE_UINT32:
            ffi_pl_arguments_set_uint32(arguments, i, SvUV(arg));
            break;
          case FFI_TYPE_SINT32:
            ffi_pl_arguments_set_sint32(arguments, i, SvIV(arg));
            break;
          case FFI_TYPE_POINTER:
            ffi_pl_arguments_set_pointer(arguments, i, SvOK(arg) ? INT2PTR(void*, SvIV(arg)) : NULL);
            break;
        }
      }
      else if(self->argument_types[i]->platypus_type == FFI_PL_STRING)
      {
        ffi_pl_arguments_set_string(arguments, i, SvOK(arg) ? SvPV_nolen(arg) : NULL);
      }
      else if(self->argument_types[i]->platypus_type == FFI_PL_POINTER)
      {
        void *ptr;
        if(SvROK(arg))
        {
          switch(self->argument_types[i]->ffi_type->type)
          {
            case FFI_TYPE_UINT8:
#ifdef HAVE_ALLOCA
              ptr = alloca(sizeof(uint8_t));
#else
              Newx(ptr, buffer_size, uint8_t);
#endif
              *((uint8_t*)ptr) = SvUV(SvRV(arg));
              break;
          }
        }
        else
        {
          ptr = NULL;
        }
        ffi_pl_arguments_set_pointer(arguments, i, ptr);
      }
    }

    ffi_call(&self->ffi_cif, self->address, &result, ffi_pl_arguments_pointers(arguments));

    for(i=0; i<items-(EXTRA_ARGS); i++)
    {
      if(self->argument_types[i]->platypus_type == FFI_PL_POINTER)
      {
        void *ptr = ffi_pl_arguments_get_pointer(arguments, i);
        if(ptr != NULL)
        {
          arg = ST(i+(EXTRA_ARGS));
          if(!SvREADONLY(SvRV(arg)))
          {
            switch(self->argument_types[i]->ffi_type->type)
            {
              case FFI_TYPE_UINT8:
                sv_setuv(SvRV(arg), *((uint8_t*)ptr));
                break;
            }
          }
        }
#ifndef HAVE_ALLOCA
        Safefree(ptr);
#endif
      }
    }
#ifndef HAVE_ALLOCA
    Safefree(buffer);
#endif

    if(self->return_type->platypus_type == FFI_PL_FFI && self->return_type->ffi_type->type == FFI_TYPE_VOID)
    {
      XSRETURN_EMPTY;
    }
    else if(self->return_type->platypus_type == FFI_PL_FFI)
    {
      if(self->return_type->ffi_type->type == FFI_TYPE_POINTER && ((void*) result) == NULL)
      {
        XSRETURN_EMPTY;
      }
      else
      {
        arg = ST(0) = sv_newmortal();
        switch(self->return_type->ffi_type->type)
        {
          case FFI_TYPE_UINT8:
            sv_setuv(arg, (uint8_t) result);
            break;
          case FFI_TYPE_SINT8:
            sv_setiv(arg, (int8_t) result);
            break;
          case FFI_TYPE_UINT16:
            sv_setuv(arg, (uint16_t) result);
            break;
          case FFI_TYPE_SINT16:
            sv_setiv(arg, (int16_t) result);
            break;
          case FFI_TYPE_UINT32:
            sv_setuv(arg, (uint32_t) result);
            break;
          case FFI_TYPE_SINT32:
            sv_setiv(arg, (int32_t) result);
            break;
          case FFI_TYPE_POINTER:
            sv_setiv(arg, PTR2IV((void*) result));
            break;
        }
        XSRETURN(1);
      }
    }
    else if(self->return_type->platypus_type == FFI_PL_STRING)
    {
      if( ((char*)result) == NULL )
      {
        XSRETURN_EMPTY;
      }
      else
      {
        arg = ST(0) = sv_newmortal();
        sv_setpv(arg, (char*)result);
      }
    }
    else if(self->return_type->platypus_type == FFI_PL_POINTER)
    {
      void *ptr = (void*) result;
      if(ptr == NULL)
      {
        XSRETURN_EMPTY;
      }
      else
      {
        SV *value = sv_newmortal();
        switch(self->return_type->ffi_type->type)
        {
          case FFI_TYPE_UINT8:
            sv_setuv(value, *((uint8_t*) result));
            break;
        }
        arg = ST(0) = newRV_inc(value);
        XSRETURN(1);
      }
    }


#undef EXTRA_ARGS
