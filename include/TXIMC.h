#ifndef TXIMC_H
#define TXIMC_H
//
// XIMC.h
//  Class to control of 8SMC4-USB from ROOT
//  Using libximc library
//
//  Liejian 15 Feb 2017
//

#include "../lib/ximc/ximc.h"

#include "TObject.h"
#include "TSystem.h"

class TXIMC : public TObject{
    public:
        device_t x_device=1;
        device_t y_device=2;
        device_t z_device=3;

        TXIMC();
        ~TXIMC();
        bool initXIMC();
        const wchar_t* error_string(result_t result);
        void Print_state(device_t device);
        void Print_state(status_t* state);
        get_position_t*  GetPosition(device_t device);  
        bool  GoLeft(device_t device);
        bool  GoRight(device_t device);
        bool  GoPositions(device_t device, int positions, int upositions=0);
        bool  Movr(device_t device, int shift, int ushift=0);
        bool  Stop(device_t device);
        bool  GoHome(device_t device);
        bool  SetDevice(device_t *device, device_t id);

        ClassDef(TXIMC,1)

    private:
       device_enumeration_t m_devenum;
       device_t m_device;
       char m_device_name[256];
};
#endif
