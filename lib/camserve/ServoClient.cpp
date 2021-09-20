// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include "ServoClient.h"

ServoClient ServoClient::defaultClients[] = {
    ServoClient{44, 0, 2},
    ServoClient{99, 2, 2},
};

ServoClient *ServoClient::clients = defaultClients;
