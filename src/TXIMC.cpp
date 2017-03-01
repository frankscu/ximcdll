#include "TXIMC.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

ClassImp(TXIMC)

TXIMC::TXIMC(){
    initXIMC();
}

bool TXIMC::initXIMC(){
    int names_count;
    int i;
    const int probe_devices=0;

	m_devenum = enumerate_devices( probe_devices, NULL );
	if (!m_devenum){
		wprintf( L"error enumerating devices\n" );
		names_count = 0;
	}

	names_count = get_device_count( m_devenum );
	if (names_count == -1){
		wprintf( L"error enumerating device\n" );
		names_count = 0;
	}

    if (names_count == 0){
        wprintf( L"No devices found\n" );
        return false;
    } 

    for (i = 0; i < names_count; ++i){
        wprintf( L"device: %hs\n", get_device_name( m_devenum, i ) );
    }
    wprintf( L"\n\nOpening device...\n\n");

    for (i = 0; i < names_count; ++i){
        strcpy( m_device_name, get_device_name( m_devenum, i ) );
        
        m_device = open_device( m_device_name );
        memset(m_device_name,0,sizeof(m_device_name)/sizeof(char));
        
        if (m_device == device_undefined){
            wprintf( L"error opening device\n" );
            return false;
        } else{
            wprintf( L"No.%d devices is openned\n", m_device);
        }
    }
    free_enumerate_devices( m_devenum );
    return true;
}

const wchar_t* TXIMC::error_string(result_t result){
    switch (result)
    {
        case result_error:				return L"error";
        case result_not_implemented:	return L"not implemented";
        case result_nodevice:			return L"no device";
        default:						return L"success";
    }
}

void TXIMC::Print_state(device_t device){
    result_t result;	
    status_t *state;
    state  = (status_t *)malloc(sizeof(status_t));

    if ((result = get_status( device, state )) != result_ok)
        wprintf( L"error getting status: %ls\n", error_string( result ) );

    wprintf( L" rpm: %d", state->CurSpeed );
    wprintf( L" pos: %d", state->CurPosition );
    wprintf( L" upwr: %d", state->Upwr );
    wprintf( L" ipwr: %d", state->Ipwr );
    wprintf( L" flags: %x", state->Flags );
    wprintf( L" mvsts: %x", state->MvCmdSts );
    if (state->Flags & STATE_ALARM)
        wprintf( L" ALARM" );
    if (state->Flags & STATE_ERRC)
        wprintf( L" ERRC" );
    if (state->Flags & STATE_ERRD)
        wprintf( L" ERRD" );
    wprintf( L"\n" );
}

void TXIMC::Print_state(status_t* state){
    result_t result;	

    wprintf( L" rpm: %d", state->CurSpeed );
    wprintf( L" pos: %d", state->CurPosition );
    wprintf( L" upwr: %d", state->Upwr );
    wprintf( L" ipwr: %d", state->Ipwr );
    wprintf( L" flags: %x", state->Flags );
    wprintf( L" mvsts: %x", state->MvCmdSts );
    if (state->Flags & STATE_ALARM)
        wprintf( L" ALARM" );
    if (state->Flags & STATE_ERRC)
        wprintf( L" ERRC" );
    if (state->Flags & STATE_ERRD)
        wprintf( L" ERRD" );
    wprintf( L"\n" );
}

// the_get_position is a struct
// int Position: The positions of the whole steps in the engine
// int uPosition: Microstep position is only used with stepper motors
// int EncPosition: Encoder position.
get_position_t* TXIMC::GetPosition(device_t device){
    result_t result; 
    get_position_t *the_get_position;
    the_get_position  = (get_position_t *)malloc(sizeof(get_position_t));

    if ((result = get_position( device, the_get_position )) != result_ok){
        wprintf( L"error get position %ls\n", error_string( result ) );
    }
    return the_get_position;
}

bool TXIMC::GoLeft(device_t device){
    result_t result;
    if ((result = command_left( device )) != result_ok){
        wprintf( L"error command left %ls\n", error_string( result ) );
        return false;
    }
    return true;
}

bool TXIMC::GoRight(device_t device){
    result_t result;
        if ((result = command_right( device )) != result_ok){
            wprintf( L"error command right %ls\n", error_string( result ) );
            return false;
        }
        return true;
    }

    bool TXIMC::Movr(device_t device, int shift, int ushift){
        result_t result;	
        status_t state;

    if ((result = get_status( device, &state )) != result_ok) {
		wprintf( L"error getting status %ls\n", error_string( result ) );
		shift = 0;
	} else {
		shift += state.CurPosition;
	}
	
    Print_state( &state );

	if ((result = command_movr ( device, shift, ushift)) != result_ok){
		wprintf( L"error command_movr %ls\n", error_string( result ) );
        return false;
    }
    return true;
}

bool TXIMC::GoPositions(device_t device, int positions, int upositions){
    result_t result;	
    status_t state;

    if ((result = get_status( device, &state )) != result_ok) {
		wprintf( L"error getting status %ls\n", error_string( result ) );
        return false;
	}
    
    Print_state( &state );

	if ((result = command_move ( device, positions, upositions)) != result_ok){
		wprintf( L"error command_move %ls\n", error_string( result ) );
        return false;
    }
    return true;
}

bool TXIMC::Stop(device_t device){
    result_t result;
    if ((result = command_stop( device )) != result_ok){
		wprintf( L"error command stop %ls\n", error_string( result ) );
        return false;
    }
    return true;
}

bool TXIMC::GoHome(device_t device){
    result_t result;
    if ((result = command_home( device )) != result_ok){
		wprintf( L"error command home %ls\n", error_string( result ) );
        return false;
    }
    return true;
}

bool TXIMC::SetDevice(device_t *device, device_t id){
    if (id == device_undefined){
        wprintf( L"error setting device %d\n", device );
        return false;
    } else{
        *device = id;
        wprintf( L"setting device %d done\n", *device );
    }
    return true;
}

TXIMC::~TXIMC(){
    result_t result;
    if ((result = close_device( &m_device )) != result_ok)
        wprintf( L"error closing device %ls\n", error_string( result ) );

    wprintf( L"Done\n" );
}
