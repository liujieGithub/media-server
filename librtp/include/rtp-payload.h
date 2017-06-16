#ifndef _rtp_payload_h_
#define _rtp_payload_h_

// https://en.wikipedia.org/wiki/RTP_audio_video_profile

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rtp_payload_t
{
	void* (*alloc)(void* param, int bytes);
	void (*free)(void* param, void *packet);
	void (*packet)(void* param, const void *packet, int bytes, int64_t time, int flags);
};

/// Create RTP packet encoder
/// @param[in] payload RTP payload type, value: [0, 127] (see more about rtp-profile.h)
/// @param[in] name RTP payload name
/// @param[in] seq RTP header sequence number filed
/// @param[in] ssrc RTP header SSRC filed
/// @param[in] handler user-defined callback functions
/// @param[in] cbparam user-defined parameter
/// @return NULL-error, other-ok
void* rtp_payload_encode_create(int payload, const char* name, uint16_t seq, uint32_t ssrc, uint32_t frequency, struct rtp_payload_t *handler, void* cbparam);
void rtp_payload_encode_destroy(void* encoder);

/// Get rtp last packet sequence number and timestamp
/// @param[in] encoder RTP packet encoder(create by rtp_payload_encode_create)
/// @param[in] data stream data
/// @param[in] bytes stream length in bytes
/// @param[in] time stream UTC time
/// @return 0-ok, ENOMEM-alloc failed, <0-failed
void rtp_payload_encode_getinfo(void* encoder, uint16_t* seq, uint32_t* timestamp);

/// Encode RTP packet
/// @param[in] encoder RTP packet encoder(create by rtp_payload_encode_create)
/// @param[in] data stream data
/// @param[in] bytes stream length in bytes
/// @param[in] time stream UTC time
/// @return 0-ok, ENOMEM-alloc failed, <0-failed
int rtp_payload_encode_input(void* encoder, const void* data, int bytes, int64_t time);


/// Create RTP packet decoder
/// @param[in] payload RTP payload type, value: [0, 127] (see more about rtp-profile.h)
/// @param[in] name RTP payload name
/// @param[in] handler user-defined callback functions
/// @param[in] cbparam user-defined parameter
/// @return NULL-error, other-ok
void* rtp_payload_decode_create(int payload, const char* name, struct rtp_payload_t *handler, void* cbparam);
void rtp_payload_decode_destroy(void* decoder);

/// Decode RTP packet
/// @param[in] decoder RTP packet decoder(create by rtp_payload_decode_create)
/// @param[in] packet RTP packet, include rtp header(12 bytes)
/// @param[in] bytes RTP packet length in bytes
/// @param[in] time stream UTC time
/// @return 0-ok, <0-failed
int rtp_payload_decode_input(void* decoder, const void* packet, int bytes, int64_t time);

/// Set/Get rtp encode packet size(don't include rtp header)
void rtp_packet_setsize(int bytes);
int rtp_packet_getsize();

#ifdef __cplusplus
}
#endif
#endif /* !_rtp_payload_h_ */