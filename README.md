# Blowfish File Encryption (S-Drive)

A proof-of-concept **Secure Distributed Drive (S-Drive)** system that lets multiple clients share
Blowfish-encrypted files over a TCP network.

## Architecture

```
┌─────────────────┐        TCP :3000        ┌──────────────────┐
│  blowfishcpp    │◄──────────────────────►│  sample_server   │
│  (full client)  │                         │  (multi-threaded)│
└─────────────────┘                         └────────┬─────────┘
                                                     │ broadcast
┌─────────────────┐                         ┌────────▼─────────┐
│  SDrive_client  │◄──────────────────────►│  other clients   │
│  (simple send)  │                         └──────────────────┘
└─────────────────┘
```

| Component | Language | Purpose |
|-----------|----------|---------|
| `blowfishcpp/` | C++ | Full client: encrypt, decrypt, key management, file sync |
| `SDrive_server/` | C | Multi-threaded server: accepts connections, broadcasts file metadata |
| `SDrive_client/` | C++ | Simple client: sends a filename + key to the server |

## Requirements

- GCC / G++ (C11 / C++11)
- OpenSSL development libraries (`libssl-dev` / `openssl-devel`)
- POSIX threads (included in glibc)

```bash
# Debian / Ubuntu
sudo apt-get install build-essential libssl-dev
```

## Build

```bash
make all        # build all three components
make server     # build only the server
make client     # build only the simple client
make blowfishcpp # build only the full client
make clean      # remove compiled binaries
```

Binaries are placed next to their source files:
- `SDrive_server/Debug/sample_server`
- `SDrive_client/sample_client`
- `blowfishcpp/blowfishcpp`

## Usage

### 1. Start the server

```bash
./SDrive_server/Debug/sample_server
# Listens on TCP port 3000
```

### 2. Run the full client

```bash
./blowfishcpp/blowfishcpp <plaintext_file> <encrypted_file> [decrypted_output]
```

The interactive menu:

```
E - Encrypt and send a file to S-Drive
D - Decrypt a file
G - Generate a key
P - Print a key from keyfile
S - Sync a file with S-Drive
R - Remove a file from S-Drive
M - Send Message to Server
X - Listen for messages
Q - Quit
```

**Typical workflow:**

```bash
# 1. Generate a 128-bit key
G → enter key filename, e.g. mykey

# 2. Encrypt and send
E → enter key filename: mykey
    (uses argv[1] as plaintext, argv[2] as ciphertext output)

# 3. On another machine: listen for incoming file notifications
X

# 4. Decrypt a received file
D → enter key filename
```

### 3. Simple client (key exchange helper)

```bash
./SDrive_client/sample_client
# Prompts for a key filename, sends "test$<key>" to localhost:3000
```

## Message Protocol

Messages are `$`-delimited strings:

```
$<client_id>$<access_group>$<message_type>$<filename>$<key>$
```

| Field | Example | Meaning |
|-------|---------|---------|
| `client_id` | `12345678` | `gethostid()` of sender |
| `access_group` | `A` | Always `"A"` (single group) |
| `message_type` | `IN` / `AD` / `TE` | Init / Add-file / Terminate |
| `filename` | `secret.enc` | Encrypted file name |
| `key` | `<16 bytes>` | Raw 128-bit Blowfish key |

## Known Limitations

> This is a proof-of-concept. It is **not** suitable for production use.

- **Hardcoded paths**: The S-Drive path is hardcoded to `/home/bala/S_drive/`. Change the
  `PATH` string in `blowfishcpp/main.cpp` (`sync()` and `remove()` functions) to match your
  environment.
- **Hardcoded address**: Server address is always `localhost:3000`. No configuration file
  support yet.
- **No authentication**: Clients are trusted implicitly; there is no challenge/response or
  certificate-based authentication.
- **Binary key in text protocol**: The 16-byte raw key is embedded in a `$`-delimited text
  message, which breaks if key bytes include `$` or `\0`. A future version should use
  Base64 encoding.
- **Thread limit**: `tid[3]` in the server supports at most 3 simultaneous client threads.
- **No graceful shutdown**: The server runs in an infinite loop and must be killed with
  `Ctrl-C`.

## Security Notes

- Keys are generated from `/dev/random` (cryptographically secure).
- Blowfish is used in CBC mode with a zero IV. For stronger security, generate a random IV
  per file and store/transmit it alongside the ciphertext.
- Filenames passed to `sync()` and `remove()` are validated against an allowlist of safe
  characters before being passed to `system()`. Filenames containing shell metacharacters
  are rejected.
