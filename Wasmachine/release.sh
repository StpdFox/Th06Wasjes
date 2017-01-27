#!/bin/bash

	sshpass -p henk scp -P 12386 Release_ARM/Wachmachine pi@10.0.1.102:Documents/Wasmachine/

#dpkg-deb --build /home/cornelis/Repositories/Install/IRPS-Install/IRPS .
echo "Done"
