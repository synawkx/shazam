#ifndef CONNECTION_H
#define CONNECTION_H

#include "common.h"

//prevent use htons
#define mc_htons(in) (in << 8) | HIBYTE(in)
//prevent use inet_addr
inline unsigned int mc_iaddr(const char* ip){
	_RtlIpv4StringToAddressA RtlIpv4StringToAddressA= (_RtlIpv4StringToAddressA)ntFunction("RtlIpv4StringToAddressA");

	PCSTR pcip = (PCSTR)ip;
	struct in_addr Addr;

	if ( *pcip == 32 && !pcip[1] )
		return 0;

	if ( RtlIpv4StringToAddressA(pcip, 0, &pcip, &Addr) < 0 )
		return -1;
	if ( !*pcip || __isascii(*pcip) && isspace(*(unsigned int *)pcip) )
		return Addr.S_un.S_addr;
	return -1;
}

void init_conn(SZSOCKET **szSocket);
void SzCreateConnection(SZCONNECTION **connection);

#endif
