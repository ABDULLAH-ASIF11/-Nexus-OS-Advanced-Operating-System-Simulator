#include "ipc.h"

#include <unistd.h>

bool createPipe(int fds[2]) { return pipe(fds) == 0; }

bool childSendRequest(int writeFd, const ResourceRequest& req) {
  ssize_t n = write(writeFd, &req, sizeof(req));
  return n == static_cast<ssize_t>(sizeof(req));
}

bool parentReadRequest(int readFd, ResourceRequest* req) {
  ssize_t n = read(readFd, req, sizeof(*req));
  return n == static_cast<ssize_t>(sizeof(*req));
}
