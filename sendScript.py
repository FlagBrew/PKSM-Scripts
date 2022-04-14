#!/usr/bin/env python3
import socket, os, sys, struct


def send(file, ip):
    host = ip
    port = 34567
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        s.sendall(struct.pack('i', os.fstat(file.fileno()).st_size))
    input("Press enter to send data")
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        data = file.read()
        s.sendall(data)


def sendName(name, ip):
    host = ip
    port = 34567
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        s.sendall(struct.pack('i', len(name.encode())))
    input("Press enter to send the filename")
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        s.sendall(name.encode())


def main(args):
    filename = ""
    ip = ""
    argCount = len(args)

    if argCount == 1:
        filename = input("Please enter the filename of the script to send: ")
        ip = input("Please enter PKSM's IP: ")
    elif argCount == 2:
        filename = args[1]
        ip = input("Please enter PKSM's IP: ")
    elif argCount == 3:
        filename = args[1]
        ip = args[2]
    with open(filename,'rb') as f:
        # send filename without subdirectories
        sendName(os.path.basename(filename), ip)
        input("name sent, press enter to send script")
        send(f, ip)


if __name__ == '__main__':
	main(sys.argv)
