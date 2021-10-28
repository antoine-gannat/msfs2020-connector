#include <iostream>
#include <Windows.h>
#include "SimConnect.h"
#include "Serial.h"

HANDLE handle;
HWND hwnd;
const int WM_USER_SIMCONNECT = 0x0402;

enum DATA_DEFINE_ID {
    DEFINITION_1,
    DEFINITION_2
};

enum DATA_REQUEST_ID {
    REQUEST_1,
    REQUEST_2,
};

struct Struct1
{
    double  kohlsmann;
    double  altitude;
    double  latitude;
    double  longitude;
};

Struct1 lastPos;

void callback(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext) {
    SIMCONNECT_RECV_SIMOBJECT_DATA* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;
    Struct1* pS = (Struct1*)&pObjData->dwData;

    lastPos = *pS;
    if (pObjData->dwRequestID == REQUEST_2) {
        std::cout << "callback alt:" << pS->altitude << ", cbData : " << cbData << std::endl;
    }
    else {
        std::cout << "callback data" << pObjData->dwData << std::endl;
    }
}

double getAltFromSerial() {
    const double maxAlt = 30000.0;
    const int potentiometerMax = 1023;

    const char* buff = readSerial();

    if (buff == nullptr) {
        return -1;
    }
    const double val = atoi(buff);
    const double alt = (maxAlt * val) / potentiometerMax;
    return std::round(alt / 100.0) * 100.0;
}


int main()
{
    initSerial();
    try {
        SimConnect_Open(&handle, "Managed Data Request", hwnd, WM_USER_SIMCONNECT, nullptr, 0);
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
        return (1);
    }

    if (SimConnect_AddToDataDefinition(handle, DEFINITION_1, "AUTOPILOT ALTITUDE LOCK VAR", "feet") == E_FAIL) {
        std::cout << "Failed to add def" << std::endl;
    }
    double lastAlt = -1;
    while (1) {
        SimConnect_CallDispatch(handle, callback, nullptr);
        double alt = getAltFromSerial();
        if (alt >= 0 && (lastAlt == -1 || (abs(lastAlt - alt) >= 100 && abs(lastAlt - alt) <= 2000))) {
            lastAlt = alt;
            if (SimConnect_SetDataOnSimObject(handle, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(alt), &alt) == E_FAIL) {
                std::cout << "Failed to write" << std::endl;
            }
        }
    }
    stopSerial();
    SimConnect_Close(handle);
    return (0);
}
