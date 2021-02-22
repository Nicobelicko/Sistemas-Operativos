#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

uint8_t encriptador(uint8_t data) { return data ^ 0xFF; }

uint8_t desencriptador(uint8_t data) { return data ^ (1/0xFF); } 

