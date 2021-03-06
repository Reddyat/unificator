#!/usr/bin/env python3

import argparse
import socket
import sys

parser = argparse.ArgumentParser()
parser.add_argument("-i", "--ip", help="Ip address to listen.")
parser.add_argument("-p", "--port", help="Port to listen.", type=int)
args = parser.parse_args()

if not args.ip or not args.port:
    print("Ip and port are mandatory.")
    parser.print_help(sys.stderr)
    sys.exit(-1)


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = (args.ip, args.port)
print("Listen on {} port {}".format(server_address[0], server_address[1]))
sock.bind(server_address)

while True:
    print(sock.recv(4096).decode())