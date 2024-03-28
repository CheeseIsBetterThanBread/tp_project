#pragma once

#include "../../include/connection/RemoteServer.h"

RemoteServer::RemoteServer() = default;

RemoteServer* RemoteServer::get_pointer() {
  return this;
}