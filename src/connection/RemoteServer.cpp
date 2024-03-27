#pragma once

#include "RemoteServer.h"

RemoteServer::RemoteServer() = default;

RemoteServer* RemoteServer::get_pointer() {
  return this;
}