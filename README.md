# Minitalk

A tiny client–server messaging program where the **only** communication channel is UNIX signals. The client sends a string to the server bit by bit using `SIGUSR1` and `SIGUSR2`; the server rebuilds the characters and prints them.

## How it works

```
client                                   server
  │  'A' = 0 1 0 0 0 0 0 1                 │
  │ ── SIGUSR2 (0) ──────────────────────▶ │  c = c << 1
  │ ── SIGUSR1 (1) ──────────────────────▶ │  c = (c << 1) | 1
  │      ... 8 signals per character ...   │
  │                                        │  after 8 bits → write(c)
```

- **Client:** for every character, sends its 8 bits from the most significant bit to the least significant bit — `SIGUSR1` for `1`, `SIGUSR2` for `0` — with a short `usleep` between signals so the server can keep up.
- **Server:** prints its PID on startup, then uses a signal handler with static state to shift each received bit into a byte. After 8 bits, the character is written to stdout.

## Build & run

```bash
make
```

Terminal 1:

```bash
./server
# Server started. PID: 12345
```

Terminal 2:

```bash
./client 12345 "Hello from Minitalk!"
```

The message appears in the server's terminal. The server keeps running and can receive messages from multiple clients one after another.

## What I learned

- UNIX signals, `kill()` and signal handlers
- Bitwise operations to encode / decode data
- Timing issues and why signals can be lost if sent too fast

## License

MIT
