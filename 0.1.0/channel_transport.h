/*
SWIGS (Shallow Water in Irregular Geometries Simulator): a software to simulate
transient or steady flows with solute transport in channels, channel networks
and rivers.

Copyright 2005-2014 Javier Burguete Tolosa.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice,
		this list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice,
		this list of conditions and the following disclaimer in the
		documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Javier Burguete Tolosa ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL Javier Burguete Tolosa OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CHANNEL_TRANSPORT__H
#define CHANNEL_TRANSPORT__H 1

#include "transport.h"
#include "initial_transport.h"
#include "boundary_transport.h"

typedef struct
{
	int n;
	InitialTransport it[1];
	BoundaryTransport *bt;
} ChannelTransport;

static inline void _channel_transport_print(ChannelTransport *ct,FILE *file)
{
	int i;
	fprintf(file,"channel_transport_print: start\n");
	initial_transport_print(ct->it,file);
	for (i=0; i<=ct->n; ++i) boundary_transport_print(ct->bt+i,file);
	fprintf(file,"channel_transport_print: end\n");
}

#if INLINE_CHANNEL_TRANSPORT_PRINT
	#define channel_transport_print _channel_transport_print
#else
	void channel_transport_print(ChannelTransport*,FILE*);
#endif

static inline void _channel_transport_error(ChannelTransport *ct,char *m)
{
	char *buffer;
	#if DEBUG_CHANNEL_TRANSPORT_ERROR
		fprintf(stderr,"channel_transport_error: start\n");
	#endif
	buffer=message;
	message=g_strconcat(gettext("Channel transport"), "\n", m, NULL);
	g_free(buffer);
	#if DEBUG_CHANNEL_TRANSPORT_ERROR
		fprintf(stderr,"channel_transport_error: end\n");
	#endif
}

#if INLINE_CHANNEL_TRANSPORT_ERROR
	#define channel_transport_error _channel_transport_error
#else
	void channel_transport_error(ChannelTransport*,char*);
#endif

static inline void _channel_transport_delete_bt(ChannelTransport *ct,int i)
{
	register int j;
	register BoundaryTransport *bt = ct->bt + i;
	#if DEBUG_CHANNEL_TRANSPORT_DELETE_BT
		fprintf(stderr,"channel_transport_delete bt: start\n");
	#endif
	boundary_transport_delete(bt);
	for (j=i; j<ct->n; ++j, ++bt) *bt = *(bt + 1);
	ct->bt = g_try_realloc(ct->bt, j * sizeof(BoundaryTransport));
	--ct->n;
	#if DEBUG_CHANNEL_TRANSPORT_DELETE_BT
		fprintf(stderr,"channel_transport_delete bt: end\n");
	#endif
}

#if INLINE_CHANNEL_TRANSPORT_DELETE_BT
	#define channel_transport_delete_bt _channel_transport_delete_bt
#else
	void channel_transport_delete_bt(ChannelTransport*,int);
#endif

static inline int _channel_transport_insert_bt
	(ChannelTransport *ct,BoundaryTransport *bt,int i)
{
	int j;
	BoundaryTransport *rbt;
	#if DEBUG_CHANNEL_TRANSPORT_INSERT_BT
		fprintf(stderr,"channel_transport_insert bt: start\n");
	#endif
	j = ct->n + 2;
	rbt = (BoundaryTransport*)g_try_realloc
		(ct->bt, j * sizeof(BoundaryTransport));
	if (!rbt)
	{
		boundary_transport_error(bt,gettext("Not enough memory"));
		#if DEBUG_CHANNEL_TRANSPORT_INSERT_BT
			fprintf(stderr,"channel_transport_insert bt: end\n");
		#endif
		return 0;
	}
	ct->bt = rbt;
	++ct->n;
	--j;
	for (rbt+=j; --j>=i; --rbt) *rbt = *(rbt-1);
	*rbt = *bt;
	#if DEBUG_CHANNEL_TRANSPORT_INSERT_BT
		fprintf(stderr,"channel_transport_insert bt: end\n");
	#endif
	return 1;
}

#if INLINE_CHANNEL_TRANSPORT_INSERT_BT
	#define channel_transport_insert_bt _channel_transport_insert_bt
#else
	int channel_transport_insert_bt(ChannelTransport*,BoundaryTransport*,int);
#endif

static inline void _channel_transport_delete(ChannelTransport *ct)
{
	int i;
	#if DEBUG_CHANNEL_TRANSPORT_DELETE
		fprintf(stderr,"channel_transport_delete: start\n");
	#endif
	initial_transport_delete(ct->it);
	for (i=0; i<=ct->n; ++i) boundary_transport_delete(ct->bt + i);
	jb_free_null((void**)&ct->bt);
	ct->n = -1;
	#if DEBUG_CHANNEL_TRANSPORT_DELETE
		fprintf(stderr,"channel_transport_delete: end\n");
	#endif
}

#if INLINE_CHANNEL_TRANSPORT_DELETE
	#define channel_transport_delete _channel_transport_delete
#else
	void channel_transport_delete(ChannelTransport*);
#endif

static inline int _channel_transport_copy
	(ChannelTransport *ct,ChannelTransport *ct_copy)
{
	register int i;

	#if DEBUG_CHANNEL_TRANSPORT_COPY
		fprintf(stderr,"channel_transport_copy: start\n");
		channel_transport_print(ct_copy,stderr);
	#endif
	
	if (ct == ct_copy) goto exit0;

	ct->it->n = ct->n = -1;
	ct->it->p = NULL;
	ct->bt = NULL;

	if (!initial_transport_copy(ct->it,ct_copy->it))
	{
		channel_transport_error(ct,message);
		goto exit2;
	}

	if (ct_copy->n >= 0)
	{
		ct->bt = (BoundaryTransport*)g_try_malloc
			((ct_copy->n + 1) * sizeof(BoundaryTransport));
		if (!ct->bt) goto exit1;
		for (i=0; i<=ct_copy->n; ++i)
		{
			if (!boundary_transport_copy(ct->bt+i,ct_copy->bt+i))
			{
				channel_transport_error(ct,message);
				goto exit2;
			}
			++ct->n;
		}
	}

exit0:
	#if DEBUG_CHANNEL_TRANSPORT_COPY
		channel_transport_print(ct,stderr);
		fprintf(stderr,"channel_transport_copy: end\n");
	#endif
	return 1;

exit1:
	channel_transport_error(ct,gettext("Not enough memory"));

exit2:
	channel_transport_delete(ct);
	#if DEBUG_CHANNEL_TRANSPORT_COPY
		fprintf(stderr,"channel_transport_copy: end\n");
	#endif
	return 0;
}

#if INLINE_CHANNEL_TRANSPORT_COPY
	#define channel_transport_copy _channel_transport_copy
#else
	int channel_transport_copy(ChannelTransport*,ChannelTransport*);
#endif

static inline int _channel_transport_parse_node
	(ChannelTransport *ct,xmlNode *node)
{
	int i,j;
	BoundaryTransport *bt;
	#if DEBUG_CHANNEL_TRANSPORT_PARSE_NODE
		fprintf(stderr,"channel_transport_parse node: start\n");
		fprintf(stderr,"CTPN node: %s\n",node->name);
	#endif
	i=0;
	if (!xmlStrcmp(node->name,XML_INITIAL_TRANSPORT))
	{
		#if DEBUG_CHANNEL_TRANSPORT_PARSE_NODE
			fprintf(stderr,"CTPN initial transport\n");
		#endif
		i=initial_transport_open_xml(ct->it,node);
		if (!i) channel_transport_error(ct,message);
	}
	else if (!xmlStrcmp(node->name,XML_BOUNDARY_TRANSPORT))
	{
		#if DEBUG_CHANNEL_TRANSPORT_PARSE_NODE
			fprintf(stderr,"CTPN boundary transport\n");
		#endif
		j = ct->n + 1;
		bt = (BoundaryTransport*)
			jb_try_realloc(ct->bt, (j + 1) * sizeof(BoundaryTransport));
		if (!bt)
		{
			channel_transport_error(ct,gettext("Not enough memory"));
			goto exit0;
		}
		i=boundary_transport_open_xml(bt+j,node);
		ct->bt = bt;
		if (i) ++ct->n; else channel_transport_error(ct,message);
	}
	else channel_transport_error(ct,gettext("Bad defined"));
exit0:
	#if DEBUG_CHANNEL_TRANSPORT_PARSE_NODE
		fprintf(stderr,"channel_transport_parse node: end\n");
	#endif
	return i;
}

#if INLINE_CHANNEL_TRANSPORT_PARSE_NODE
	#define channel_transport_parse_node _channel_transport_parse_node
#else
	int channel_transport_parse_node(ChannelTransport*,xmlNode *node);
#endif

static inline int _channel_transport_open_xml
	(ChannelTransport *ct,xmlNode *node)
{
	int j;

	#if DEBUG_CHANNEL_TRANSPORT_OPEN_XML
		fprintf(stderr,"channel_transport_open_xml: start\n");
	#endif
	ct->n = -1;
	ct->bt = NULL;
	j=0;
	for (node=node->children; node; node=node->next)
		if (!channel_transport_parse_node(ct,node)) goto exit0;
	#if DEBUG_CHANNEL_TRANSPORT_OPEN_XML
		channel_transport_print(ct,stderr);
	#endif
	j=1;
	goto exit1;

exit0:
	channel_transport_delete(ct);

exit1:
	#if DEBUG_CHANNEL_TRANSPORT_OPEN_XML
		fprintf(stderr,"channel_transport_open_xml: end\n");
	#endif
	return j;
}

#if INLINE_CHANNEL_TRANSPORT_OPEN_XML
	#define channel_transport_open_xml _channel_transport_open_xml
#else
	int channel_transport_open_xml(ChannelTransport*,xmlNode*);
#endif

static inline void _channel_transport_save_xml
	(ChannelTransport *ct,xmlNode *node)
{
	int i;
	xmlNode *child;
	#if DEBUG_CHANNEL_TRANSPORT_SAVE_XML
		fprintf(stderr,"channel_transport_save_xml: start\n");
		channel_transport_print(ct,stderr);
	#endif
	child=xmlNewChild(node,0,XML_INITIAL_TRANSPORT,0);
	initial_transport_save_xml(ct->it,child);
	for (i=0; i<=ct->n; ++i)
	{
		child=xmlNewChild(node,0,XML_BOUNDARY_TRANSPORT,0);
		boundary_transport_save_xml(ct->bt+i,child);
	}
	#if DEBUG_CHANNEL_TRANSPORT_SAVE_XML
		fprintf(stderr,"channel_transport_save_xml: end\n");
	#endif
}

#if INLINE_CHANNEL_TRANSPORT_SAVE_XML
	#define channel_transport_save_xml _channel_transport_save_xml
#else
	void channel_transport_save_xml(ChannelTransport*,xmlNode*);
#endif

#endif

