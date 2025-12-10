
#pragma once

#define PROTOCOL "https"
#define HOST "epcb.espitek.com"
#define PORT "443"

#define LOGIN_URL PROTOCOL "://" HOST ":" PORT "/api/auth/login"
#define RPC_PREFIX_URL   PROTOCOL "://" HOST ":" PORT "/api/rpc/twoway/"

#define STUN_SERVER "stun:epcb.espitek.com:3478"
#define TURN_SERVER "turn:turnepcb:epcb4924@epcb.espitek.com:3478"