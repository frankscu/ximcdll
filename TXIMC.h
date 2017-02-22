#ifndef TXIMC_H
#define TXIMC_H
//
// XIMC.h
//  Class to control of 8SMC4-USB from ROOT
//  Using libximc library
//
//  Liejian 15 Feb 2017
//
//#if defined(__APPLE__) && !defined(NOFRAMEWORK)
//// include path to framework
//#include <libximc/ximc.h>
//#else
//#include <ximc.h>
//#endif
#include "ximc/ximc.h"

#include "TObject.h"
#include "TSystem.h"

class TXIMC : public TObject{
    public:
        TXIMC();
        ~TXIMC();
        int initXIMC();
        const wchar_t* error_string(result_t result);
        void Print_state(device_t device);
        void Print_state(status_t* state);
        get_position_t*  GetPosition(device_t device);  
        int  GoLeft(device_t device);
        int  GoRight(device_t device);
        int  Movr(device_t device, int shift, int ushift);
        int  Stop(device_t device);
        int  GoHome(device_t device);
        
        ClassDef(TXIMC,1)
    private:
        device_enumeration_t m_devenum;
        device_t m_device;
        char m_device_name[256];
};
#endif
