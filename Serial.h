#ifndef SERIAL_H
#define SERIAL_H

int GetPorts();
int OpenPort(int port);
int ClosePort();
int Send(char *x);
int Repeat(char *x);
char * PortName(int number);

#endif /* SERIAL_H */