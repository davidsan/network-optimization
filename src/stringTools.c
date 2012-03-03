#include "stringTools.h"

int scanNbChain(char *string)
{
    int res;
    if (sscanf(string, "c NbChain: %d", &res) != 1) {
	leverErreur("lecture NbChain (format incorrect)");
	return -1;
    }
    return res;
}

int scanGamma(char *string)
{
    int res;
    if (sscanf(string, "c Gamma: %d", &res) != 1) {
	leverErreur("lecture Gamma (format incorrect)");
	return -1;
    }
    return res;
}

int scanNumero(char *string)
{
    int res;
    if (sscanf(string, "h %d ", &res) != 1) {
	leverErreur("lecture numéro (format incorrect)");
	return -1;
    }
    return res;
}
