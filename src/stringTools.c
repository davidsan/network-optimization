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

int scanNbNodes(char *string)
{
    int res;
    if (sscanf(string, "c NbNodes: %d", &res) != 1) {
	leverErreur("lecture NbNodes (format incorrect)");
	return -1;
    }
    return res;
}

int scanNbCables(char *string)
{
    int res;
    if (sscanf(string, "c NbCables: %d", &res) != 1) {
	leverErreur("lecture NbCables (format incorrect)");
	return -1;
    }
    return res;
}

int isComment(char *string)
{
    return (string[0] == 'c');
}
