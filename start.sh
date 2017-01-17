#!/bin/bash
udevd &
udevadm trigger
node server.js