#!/usr/bin/env python3
import ctypes
import os
import signal
import sys
import time

# Path to built shared library (one level up from test/)
HERE = os.path.dirname(os.path.abspath(__file__))
LIB_PATH = os.path.join(HERE, 'libp2p.so')

if not os.path.exists(LIB_PATH):
    print(f"Error: {LIB_PATH} not found. Build the project (make) first.")
    sys.exit(1)

lib = ctypes.CDLL(LIB_PATH)

# Bindings
lib.p2p_get_version.restype = ctypes.c_char_p
lib.p2p_init.restype = None
lib.p2p_login.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]
lib.p2p_login.restype = ctypes.c_int
lib.p2p_create.restype = ctypes.c_void_p
lib.p2p_destroy.argtypes = [ctypes.c_void_p]
lib.p2p_start_stream.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
lib.p2p_start_stream.restype = ctypes.c_int
lib.p2p_get_port_stream.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
lib.p2p_get_port_stream.restype = ctypes.c_uint
lib.p2p_stop_stream.argtypes = [ctypes.c_void_p, ctypes.c_char_p]

# Default constants from include/define.h
LOGIN_URL = b"https://epcb.espitek.com:443/api/auth/login"

# Example
DEV1 = b"c0774560-3870-11f0-82d4-db0fa8eab971"
USER = b"binhnt@epcb.vn"
PSK = b"123456"

loop_enable = True

def sig_handler(sig, frame):
    global loop_enable
    print("Termination signal received, exiting...")
    loop_enable = False


def main():
    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    print(f"Library version: {lib.p2p_get_version().decode()}")
    lib.p2p_init()
    ok = lib.p2p_login(LOGIN_URL, USER, PSK)
    if not ok:
        print("Login failed")
        return 1

    inst = lib.p2p_create()
    if not inst:
        print("Failed to create p2p instance")
        return 1

    lib.p2p_start_stream(inst, DEV1)
    # lib.p2p_start_stream(inst, DEV2)

    # wait a bit for streams to settle
    time.sleep(5)

    port1 = lib.p2p_get_port_stream(inst, DEV1)
    # port2 = lib.p2p_get_port_stream(inst, DEV2)

    try:
        while loop_enable:
            time.sleep(1)
    except KeyboardInterrupt:
        pass

    lib.p2p_stop_stream(inst, DEV1)
    # lib.p2p_stop_stream(inst, DEV2)

    lib.p2p_destroy(inst)

    # wait a bit to ensure cleanup messages are printed
    time.sleep(1)

    print("Exiting...")
    return 0


if __name__ == '__main__':
    sys.exit(main())
