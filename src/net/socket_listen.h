#ifndef LIBTORRENT_SOCKET_LISTEN_H
#define LIBTORRENT_SOCKET_LISTEN_H

#include <cinttypes>
#include <functional>

#include "torrent/net/fd.h"
#include "torrent/net/socket_address.h"
#include "torrent/net/socket_event.h"

namespace torrent {

class socket_listen : public socket_event {
public:
  // TODO: Add bind name, pass through bind_manager.
  typedef std::function<void (int, sa_unique_ptr)> accepted_ftor;

  socket_listen();
  // virtual ~socket_listen() {}

  int  backlog() const;

  void set_backlog(int backlog);
  void set_slot_accepted(accepted_ftor&& ftor);

  bool open(sa_unique_ptr&& sap, uint16_t first_port, uint16_t last_port, uint16_t start_port, fd_flags open_flags);
  void close();

  virtual void event_read();
  virtual void event_write();
  virtual void event_error();

  virtual const char* type_name() const { return "socket_listen"; }

private:
  bool m_open_port(int fd, sa_unique_ptr& sap, uint16_t port);

  int           m_backlog;
  accepted_ftor m_slot_accepted;
};

inline int  socket_listen::backlog() const { return m_backlog; }
inline void socket_listen::set_slot_accepted(accepted_ftor&& ftor) { m_slot_accepted = ftor; }

}

#endif
