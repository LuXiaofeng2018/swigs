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

/*
	BOUNDARY SPECIFICATIONS
	0: Constant discharge
		p1[0]=discharge
	1: Constant depth
		p1[0]=depth
	2: Constant level
		p1[0]=level
	3: Constant discharge and depth
		p1[0]=discharge, p1[1]=depth
	4: Constant discharge and level
		p1[0]=discharge, p1[1]=level
	5: Discharge hydrogram Q(t)
		p1[i]=time, p2[i]=discharge
	6: Depth hydrogram h(t)
		p1[i]=time, p2[i]=depth
	7: Depth hydrogram z(t)
		p1[i]=time, p2[i]=level
	8: Discharge and depth hydrogram Q(t), h(t)
		p1[i]=time, p2[i]=discharge, p3[i]=depth
	9: Discharge and level hydrogram Q(t), z(t)
		p1[i]=time, p2[i]=discharge, p3[i]=level
	10: Q(h)
		p1[i]=depth, p2[i]=discharge
	11: Q(z)
		p1[i]=level, p2[i]=discharge
	12: Supercritical output
	13: Dam
		data[0]=level, data[1]=roughness
		p1[i]=time, p2[i]=maximum discharge
	14: Pipe
		p1[i]=time, p2[i]=maximum discharge
	15: Gate
		data[0]=height, data[1]=width
		p1[i]=time, p2[i]=opening
	16: Junction
	17: Gauge
		data[0]=tolerance
		p1[i]=time, p2[i]=discharge
*/

#ifndef BOUNDARY_FLOW__H
#define BOUNDARY_FLOW__H 1

#include "points.h"
#include "junction_data.h"
#include "gauge_data.h"

#define N_BOUNDARY_FLOW			18
#define N_BOUNDARY_FLOW_EXTERN	15
#define N_BOUNDARY_FLOW_INNER	9

#define DAM_LEVEL(bf) (((JBFLOAT*)bf->data)[0])
#define DAM_ROUGHNESS(bf) (((JBFLOAT*)bf->data)[1])

#define GATE_HEIGHT(bf) (((JBFLOAT*)bf->data)[0])
#define GATE_WIDTH(bf) (((JBFLOAT*)bf->data)[1])

#define JUNCTION_TYPE(bf) (((int*)bf->data)[0])
#define JUNCTION_N(bf) (((int*)bf->data)[1])
#define JUNCTION_DATA(bf,i) \
	((JunctionData*)(bf->data+2*sizeof(int)+i*sizeof(JunctionData)))

#define GAUGE_TOLERANCE(bf) (((JBFLOAT*)bf->data)[0])
#define GAUGE_NINFLUENCES(bf) (((int*)(((JBFLOAT*)bf->data)+1))[0])
#define GAUGE_INFLUENCE(bf) (((GaugeInfluence*)(((JBFLOAT*)bf->data)+2))[0])

enum JunctionType
{
	JUNCTION_TYPE_FRONTAL=0,
	JUNCTION_TYPE_TRIBUTARY=1,
	JUNCTION_TYPE_PARALLEL=2
};

enum BoundaryFlowType
{
	BOUNDARY_FLOW_Q=0,
	BOUNDARY_FLOW_H=1,
	BOUNDARY_FLOW_Z=2,
	BOUNDARY_FLOW_Q_H=3,
	BOUNDARY_FLOW_Q_Z=4,
	BOUNDARY_FLOW_QT=5,
	BOUNDARY_FLOW_HT=6,
	BOUNDARY_FLOW_ZT=7,
	BOUNDARY_FLOW_QT_HT=8,
	BOUNDARY_FLOW_QT_ZT=9,
	BOUNDARY_FLOW_QH=10,
	BOUNDARY_FLOW_QZ=11,
	BOUNDARY_FLOW_SUPERCRITICAL=12,
	BOUNDARY_FLOW_DAM=13,
	BOUNDARY_FLOW_PIPE=14,
	BOUNDARY_FLOW_GATE=15,
	BOUNDARY_FLOW_JUNCTION=16,
	BOUNDARY_FLOW_GAUGE=17
};

typedef struct
{
	int type,pos,pos2,n,i,i2;
	JBFLOAT contribution;
	JBFLOAT *p1,*p2,*p3;
	char *name;
	void *data;
} BoundaryFlow;

extern int simulating, mass_inputs;

static inline void _boundary_flow_print(BoundaryFlow *bf,FILE *file)
{
	int i;
	fprintf(file,"boundary_flow_print: start\n");

	fprintf(file,"BFP name=%s\n",bf->name);
	fprintf(file,"BFP type=%d pos=%d pos2=%d\n",bf->type,bf->pos,bf->pos2);

	switch (bf->type)
	{
	case BOUNDARY_FLOW_Q_H:
	case BOUNDARY_FLOW_Q_Z:
	case BOUNDARY_FLOW_QT_HT:
	case BOUNDARY_FLOW_QT_ZT:
		for (i=0; i<=bf->n; ++i)
			fprintf(file,"BFP i=%d p3="FWF"\n",i,bf->p3[i]);
	case BOUNDARY_FLOW_Q:
	case BOUNDARY_FLOW_H:
	case BOUNDARY_FLOW_Z:
	case BOUNDARY_FLOW_QT:
	case BOUNDARY_FLOW_HT:
	case BOUNDARY_FLOW_ZT:
	case BOUNDARY_FLOW_QH:
	case BOUNDARY_FLOW_QZ:
	case BOUNDARY_FLOW_DAM:
	case BOUNDARY_FLOW_PIPE:
	case BOUNDARY_FLOW_GATE:
	case BOUNDARY_FLOW_GAUGE:
		for (i=0; i<=bf->n; ++i) fprintf(file,"BFP i=%d p1="FWF" p2="FWF"\n",
			i,bf->p1[i],bf->p2[i]);
		break;
	case BOUNDARY_FLOW_JUNCTION:
		fprintf(file,"BFP n=%d\n",JUNCTION_N(bf));
		for (i=0; i<=JUNCTION_N(bf); ++i)
			junction_data_print(JUNCTION_DATA(bf,i),file);
	}

	switch (bf->type)
	{
	case BOUNDARY_FLOW_DAM:
		fprintf(file,"BFP level="FWF" roughness="FWF"\n",
			DAM_LEVEL(bf),DAM_ROUGHNESS(bf));
		break;
	case BOUNDARY_FLOW_GATE:
		fprintf(file,"BFP height="FWF" width="FWF"\n",
			GATE_HEIGHT(bf),GATE_WIDTH(bf));
		break;
	case BOUNDARY_FLOW_GAUGE:
		fprintf(file,"BFP tolerance="FWF"\n",GAUGE_TOLERANCE(bf));
	}

	fprintf(file,"boundary_flow_print: end\n");
}

#if INLINE_BOUNDARY_FLOW_PRINT
	#define boundary_flow_print _boundary_flow_print
#else
	void boundary_flow_print(BoundaryFlow*,FILE*);
#endif

static inline void _boundary_flow_error(BoundaryFlow *bf,char *m)
{
	char *buffer;
	#if DEBUG_BOUNDARY_FLOW_ERROR
		fprintf(stderr,"boundary_flow_error: start\n");
	#endif
	buffer=message;
	message=g_strconcat(gettext("Flow boundary condition"), ": ", bf->name,
		"\n", m, NULL);
	g_free(buffer);
	#if DEBUG_BOUNDARY_FLOW_ERROR
		fprintf(stderr,"boundary_flow_error: end\n");
	#endif
}

#if INLINE_BOUNDARY_FLOW_ERROR
	#define boundary_flow_error _boundary_flow_error
#else
	void boundary_flow_error(BoundaryFlow*,char*);
#endif

static inline void _boundary_flow_delete(BoundaryFlow *bf)
{
	#if DEBUG_BOUNDARY_FLOW_DELETE
		fprintf(stderr,"boundary_flow_delete: start\n");
	#endif
	jb_free_null((void**)&bf->p1);
	jb_free_null((void**)&bf->name);
	jb_free_null((void**)&bf->data);
	#if DEBUG_BOUNDARY_FLOW_DELETE
		fprintf(stderr,"boundary_flow_delete: end\n");
	#endif
}

#if INLINE_BOUNDARY_FLOW_DELETE
	#define boundary_flow_delete _boundary_flow_delete
#else
	void boundary_flow_delete(BoundaryFlow*);
#endif

static inline int _boundary_flow_copy(BoundaryFlow *bf,BoundaryFlow *bf_copy)
{
	int i,j;
	#if DEBUG_BOUNDARY_FLOW_COPY
		fprintf(stderr,"boundary_flow_copy: start\n");
		boundary_flow_print(bf_copy,stderr);
	#endif

	if (bf == bf_copy) goto exit0;

	bf->pos = bf_copy->pos;
	bf->pos2 = bf_copy->pos2;
	bf->p1 = NULL;
	bf->data = NULL;

	bf->name = jb_strdup(bf_copy->name);
	if (!bf->name) goto exit1;
	#if DEBUG_BOUNDARY_FLOW_COPY
		fprintf(stderr,"BFC name=%s\n", bf->name);
	#endif

	bf->type = bf_copy->type;
	if (bf->type == BOUNDARY_FLOW_SUPERCRITICAL) goto exit0;

	if (bf->type != BOUNDARY_FLOW_JUNCTION)
	{
		bf->n = bf_copy->n;
		j = bf->n + 1;
		bf->p1 = (JBFLOAT*)g_try_malloc(j*2*sizeof(JBFLOAT));
		if (!bf->p1) goto exit1;
		bf->p2 = bf->p1 + j;
		memcpy(bf->p1, bf_copy->p1, j * 2 * sizeof(JBFLOAT));
	}

	switch (bf->type)
	{
	case BOUNDARY_FLOW_Q_H:
	case BOUNDARY_FLOW_Q_Z:
	case BOUNDARY_FLOW_QT_HT:
	case BOUNDARY_FLOW_QT_ZT:
		bf->p1 = (JBFLOAT*)g_try_realloc(bf->p1, j*3*sizeof(JBFLOAT));
		if (!bf->p1) goto exit1;
		bf->p2 = bf->p1 + j;
		bf->p3 = bf->p2 + j;
		memcpy(bf->p3, bf_copy->p3, j * sizeof(JBFLOAT));
		break;
	case BOUNDARY_FLOW_DAM:
	case BOUNDARY_FLOW_GATE:
		bf->data = g_try_malloc(2 * sizeof(JBFLOAT));
		if (!bf->data) goto exit1;
		memcpy(bf->data, bf_copy->data, 2 * sizeof(JBFLOAT));
		break;
	case BOUNDARY_FLOW_JUNCTION:
		#if DEBUG_BOUNDARY_FLOW_COPY
			fprintf(stderr,"BFC n=%d\n",JUNCTION_N(bf_copy));
		#endif
		i=2*sizeof(int)+(1+JUNCTION_N(bf_copy))*sizeof(JunctionData);
		bf->data = g_try_malloc(i);
		if (!bf->data) goto exit1;
		memcpy(bf->data, bf_copy->data, i);
		break;
	case BOUNDARY_FLOW_GAUGE:
		bf->data = g_try_malloc(sizeof(JBFLOAT));
		if (!bf->data) goto exit1;
		GAUGE_TOLERANCE(bf) = GAUGE_TOLERANCE(bf_copy);
	}

exit0:
	#if DEBUG_BOUNDARY_FLOW_COPY
		boundary_flow_print(bf,stderr);
		fprintf(stderr,"boundary_flow_copy: end\n");
	#endif
	return 1;

exit1:
	boundary_flow_error(bf_copy,gettext("Not enough memory"));
	boundary_flow_delete(bf);
	#if DEBUG_BOUNDARY_FLOW_COPY
		fprintf(stderr,"boundary_flow_copy: end\n");
	#endif
	return 0;
}

#if INLINE_BOUNDARY_FLOW_COPY
	#define boundary_flow_copy _boundary_flow_copy
#else
	int boundary_flow_copy(BoundaryFlow*,BoundaryFlow*);
#endif

static inline int _boundary_flow_open_xml
	(BoundaryFlow *bf,xmlNode *node,int position)
{
	int i,j;
	char *buffer;
	void *p;
	JBFLOAT x,y,z;
	FILE *file;
	xmlNode *child;
	#if DEBUG_BOUNDARY_FLOW_OPEN_XML
		fprintf(stderr,"boundary_flow_open_xml: start\n");
		fprintf(stderr,"BFOX position=%d\n",position);
	#endif

	bf->p1 = NULL;
	bf->data = NULL;
	bf->name = NULL;

	if (position<0) bf->name = jb_strdup(gettext("Inlet flow"));
	else if (position>0) bf->name = jb_strdup(gettext("Outlet flow"));
	else
	{
		if (!xmlHasProp(node,XML_NAME))
		{
			message = g_strconcat(gettext("Flow boundary condition"), "\n",
				gettext("Not name"), NULL);
			goto exit1;
		}
		buffer=(char*)xmlGetProp(node,XML_NAME);
		bf->name = jb_strdup(buffer);
		xmlFree(buffer);
		if (!xmlHasProp(node,XML_INITIAL))
		{
			boundary_flow_error(bf,gettext("Bad position"));
			goto exit1;
		}
		bf->pos = jb_xml_node_get_int(node,XML_INITIAL,&i);
		bf->pos2 =
			jb_xml_node_get_int_with_default(node, XML_FINAL, &j, bf->pos + 1);
		if (i!=1 || j!=1)
		{
			boundary_flow_error(bf,gettext("Bad position"));
			goto exit1;
		}
		if (bf->pos2 < bf->pos)
		{
			boundary_flow_error(bf,gettext("Bad order"));
			goto exit1;
		}
		#if DEBUG_BOUNDARY_FLOW_OPEN_XML
			fprintf(stderr,"BFOX pos=%d pos2=%d\n",bf->pos,bf->pos2);
		#endif
	}
	if (!bf->name)
	{
		message=g_strconcat(gettext("Flow boundary condition"), "\n",
			gettext("Not enough memory"), NULL);
		goto exit1;
	}
	#if DEBUG_BOUNDARY_FLOW_OPEN_XML
		fprintf(stderr,"BFOX name=%s\n",bf->name);
	#endif

	if (!xmlHasProp(node,XML_TYPE))
	{
		boundary_flow_error(bf,gettext("Unknow type"));
		goto exit1;
	}
	buffer=(char*)xmlGetProp(node,XML_TYPE);
	#if DEBUG_BOUNDARY_FLOW_OPEN_XML
		fprintf(stderr,"BFOX type=%s\n",buffer);
	#endif

	if (!xmlStrcmp((const xmlChar*)buffer,XML_Q))
	{
		bf->type = BOUNDARY_FLOW_Q;
		if (!xmlHasProp(node,XML_DISCHARGE))
		{
			boundary_flow_error(bf,gettext("Unknow type"));
			goto exit2;
		}
		x=jb_xml_node_get_float(node,XML_DISCHARGE,&i);
		goto type01;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_H))
	{
		bf->type = BOUNDARY_FLOW_H;
		if (!xmlHasProp(node,XML_DEPTH))
		{
			boundary_flow_error(bf,gettext("Unknow type"));
			goto exit2;
		}
		x=jb_xml_node_get_float(node,XML_DEPTH,&i);
		goto type01i;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_Z))
	{
		bf->type = BOUNDARY_FLOW_Z;
		if (!xmlHasProp(node,XML_LEVEL))
		{
			boundary_flow_error(bf,gettext("Unknow type"));
			goto exit2;
		}
		x=jb_xml_node_get_float(node,XML_LEVEL,&i);
		goto type01i;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_Q_H))
	{
		bf->type = BOUNDARY_FLOW_Q_H;
		if (!xmlHasProp(node,XML_DISCHARGE) || !xmlHasProp(node,XML_DEPTH))
		{
			boundary_flow_error(bf,gettext("Unknow type"));
			goto exit2;
		}
		x=jb_xml_node_get_float(node,XML_DISCHARGE,&i);
		y=jb_xml_node_get_float(node,XML_DEPTH,&j);
		goto type02i;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_Q_Z))
	{
		bf->type = BOUNDARY_FLOW_Q_Z;
		if (!xmlHasProp(node,XML_DISCHARGE) || !xmlHasProp(node,XML_LEVEL))
		{
			boundary_flow_error(bf,gettext("Unknow type"));
			goto exit2;
		}
		x=jb_xml_node_get_float(node,XML_DISCHARGE,&i);
		y=jb_xml_node_get_float(node,XML_LEVEL,&j);
		goto type02i;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_QT))
	{
		bf->type = BOUNDARY_FLOW_QT;
		goto type2time;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_HT))
	{
		bf->type = BOUNDARY_FLOW_HT;
		goto type2itime;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_ZT))
	{
		bf->type = BOUNDARY_FLOW_ZT;
		goto type2itime;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_QT_HT))
	{
		bf->type = BOUNDARY_FLOW_QT_HT;
		goto type3itime;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_QT_ZT))
	{
		bf->type = BOUNDARY_FLOW_QT_ZT;
		goto type3itime;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_QH))
	{
		bf->type = BOUNDARY_FLOW_QH;
		goto type2;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_QZ))
	{
		bf->type = BOUNDARY_FLOW_QZ;
		goto type2;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_SUPERCRITICAL))
	{
		bf->type = BOUNDARY_FLOW_SUPERCRITICAL;
		goto type0i;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_DAM))
	{
		bf->type = BOUNDARY_FLOW_DAM;
		if (!xmlHasProp(node,XML_LEVEL) || !xmlHasProp(node,XML_ROUGHNESS))
		{
			boundary_flow_error(bf,gettext("Bad defined"));
			goto exit2;
		}
		bf->data = g_try_malloc(2*sizeof(JBFLOAT));
		if (!bf->data);
		{
			boundary_flow_error(bf,gettext("Not enough memory"));
			goto exit2;
		}
		DAM_LEVEL(bf)=jb_xml_node_get_float(node,XML_LEVEL,&i);
		DAM_ROUGHNESS(bf)=jb_xml_node_get_float(node,XML_ROUGHNESS,&j);
		if (i!=1 || j!=1);
		{
			boundary_flow_error(bf,gettext("Bad defined"));
			goto exit2;
		}
		goto type2nitime;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_PIPE))
	{
		bf->type = BOUNDARY_FLOW_PIPE;
		if (!xmlHasProp(node,XML_FINAL))
		{
			boundary_flow_error(bf,gettext("Bad defined"));
			goto exit2;
		}
		bf->pos2 = jb_xml_node_get_int(node,XML_FINAL,&i);
		if (i!=1);
		{
			boundary_flow_error(bf,gettext("Bad defined"));
			goto exit2;
		}
		goto type2nitime;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_GATE))
	{
		bf->type = BOUNDARY_FLOW_GATE;
		if (!xmlHasProp(node,XML_HEIGHT) || !xmlHasProp(node,XML_WIDTH))
			goto exit2;
		bf->data = g_try_malloc(2*sizeof(JBFLOAT));
		if (!bf->data) goto exit2;
		GATE_HEIGHT(bf)=jb_xml_node_get_float(node,XML_HEIGHT,&i);
		GATE_WIDTH(bf)=jb_xml_node_get_float(node,XML_WIDTH,&j);
		if (i!=1 || j!=1) goto exit2;
		goto type2itime;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_JUNCTION))
	{
		bf->type = BOUNDARY_FLOW_JUNCTION;
		bf->data = g_try_malloc(2*sizeof(int));
		if (!bf->data) goto exit1;
		JUNCTION_N(bf)=-1;
		for (child=node->children; child; child=child->next)
		{
			++JUNCTION_N(bf);
			bf->data = jb_realloc(bf->data, 
				2 * sizeof(int) + (1 + JUNCTION_N(bf)) * sizeof(JunctionData));
			if (!bf->data) goto exit1;
			junction_data_open_xml(JUNCTION_DATA(bf,JUNCTION_N(bf)),child);
		}
		if (JUNCTION_N(bf)<0)
		{
			boundary_flow_error(bf,gettext("Bad junction"));
			goto exit2;
		}
		goto exit0;
	}
	else if (!xmlStrcmp((const xmlChar*)buffer,XML_GAUGE))
	{
		bf->type = BOUNDARY_FLOW_GAUGE;
		bf->data = g_try_malloc(2*sizeof(JBFLOAT));
		if (!bf->data) goto exit1;
		if (xmlHasProp(node,XML_TOLERANCE))
		{
			x=jb_xml_node_get_float(node,XML_TOLERANCE,&i);
			if (i!=1 || x<0.)
			{
				boundary_flow_error(bf,gettext("Bad tolerance"));
				goto exit2;
			}
			GAUGE_TOLERANCE(bf)=x;
		}
		else GAUGE_TOLERANCE(bf)=0.;
		GAUGE_NINFLUENCES(bf)=0;
		for (child=node->children; child; child=child->next)
		{
			if (!xmlStrcmp(child->name, XML_INFLUENCE))
			{
				bf->data = jb_realloc(bf->data, 2 * sizeof(JBFLOAT) +
					(1 + GAUGE_NINFLUENCES(bf)) * sizeof(GaugeInfluence));
				if (!bf->data) goto exit1;
				++GAUGE_NINFLUENCES(bf);
			}
			if (!xmlStrcmp(child->name, XML_HYDROGRAM)) goto type2nitime;
		}
		boundary_flow_error(bf,gettext("Not hydrogram"));
		goto exit2;
	}
	else
	{
		boundary_flow_error(bf,gettext("Unknow type"));
		goto exit2;
	}

type3itime:
	if (!position)
	{
		boundary_flow_error(bf,gettext("Unknow type"));
		goto exit2;
	}

/*type3time:*/
	xmlFree(buffer);
	file=jb_xml_node_get_content_file(node,&buffer);
	if (!file)
	{
		boundary_flow_error(bf,gettext("Not enough memory"));
		goto exit2;
	}
	j=-1;
	p=0;
	do
	{
		x=jb_get_time_file(file,&i);
		if (!i) break;
		if (i!=6)
		{
			boundary_flow_error(bf,gettext("Bad time"));
			goto exit4;
		}
		i=fscanf(file,FRF FRF,&y,&z);
		if (i<2) break;
		++j;
		p = (Point3*)g_try_realloc(p, (j + 1) * sizeof(Point3));
		if (!p)
		{
			boundary_flow_error(bf,gettext("Not enough memory"));
			goto exit4;
		}
		point3_open(((Point3*)p)+j,x,y,z);
	}
	while (1);
	bf->n = j;
	++j;
	bf->p1 = (JBFLOAT*)g_try_malloc(j * 3 *sizeof(JBFLOAT));
	if (!bf->p1)
	{
		boundary_flow_error(bf,gettext("Not enough memory"));
		goto exit4;
	}
	bf->p2 = bf->p1 + j;
	bf->p3 = bf->p2 + j;
	for (i=j; --i>=0;)
	{
		bf->p1[i] = ((Point3*)p)[i].x;
		bf->p2[i] = ((Point3*)p)[i].y;
		bf->p3[i] = ((Point3*)p)[i].z;
	}
	jb_free_null((void**)&p);
	fclose(file);
	goto exit0;

/* NOT USED
type3i:
	if (!position)
	{
		boundary_flow_error(bf,gettext("Unknow type"));
		goto exit2;
	}

type3:
	xmlFree(buffer);
	file=jb_xml_node_get_content_file(node,&buffer);
	if (!file)
	{
		boundary_flow_error(bf,gettext("Not enough memory"));
		goto exit2;
	}
	j=-1;
	p=0;
	do
	{
		i=fscanf(file,FRF FRF FRF,&x,&y,&z);
		if (i<3) break;
		++j;
		p = (Point3*)g_try_realloc(p, (j + 1) * sizeof(Point3));
		if (!p)
		{
			boundary_flow_error(bf,gettext("Not enough memory"));
			goto exit4;
		}
		point3_open(((Point3*)p)+j,x,y,z);
	}
	while (1);
	bf->n = j;
	++j;
	bf->p1 = (JBFLOAT*)g_try_malloc(j * 3 *sizeof(JBFLOAT));
	if (!bf->p1)
	{
		boundary_flow_error(bf,gettext("Not enough memory"));
		goto exit4;
	}
	bf->p2 = bf->p1 + j;
	bf->p3 = bf->p2 + j;
	for (i=j; --i>=0;)
	{
		bf->p1[i] = ((Point3*)p)[i].x;
		bf->p2[i] = ((Point3*)p)[i].y;
		bf->p3[i] = ((Point3*)p)[i].z;
	}
	jb_free_null((void**)&p);
	fclose(file);
	goto exit0;
*/

type2nitime:
	if (position)
	{
		boundary_flow_error(bf,gettext("Unknow type"));
		goto exit2;
	}
	goto type2time;

type2itime:
	if (!position)
	{
		boundary_flow_error(bf,gettext("Unknow type"));
		goto exit1;
	}

type2time:
	xmlFree(buffer);
	file=jb_xml_node_get_content_file(node,&buffer);
	if (!file)
	{
		boundary_flow_error(bf,gettext("Not enough memory"));
		goto exit1;
	}
	j=-1;
	p=NULL;
	do
	{
		x=jb_get_time_file(file,&i);
		if (!i) break;
		if (i!=6)
		{
			boundary_flow_error(bf,gettext("Bad time"));
			goto exit4;
		}
		i=fscanf(file,FRF,&y);
		if (i<1) break;
		++j;
		p = (Point2*)g_try_realloc(p, (j + 1) * sizeof(Point2));
		if (!p)
		{
			boundary_flow_error(bf,gettext("Not enough memory"));
			goto exit4;
		}
		point2_open(((Point2*)p)+j,x,y);
	}
	while (1);
	bf->n = j;
	++j;
	bf->p1 = (JBFLOAT*)g_try_malloc(j * 2 *sizeof(JBFLOAT));
	if (!bf->p1)
	{
		boundary_flow_error(bf,gettext("Not enough memory"));
		goto exit4;
	}
	bf->p2 = bf->p1 + j;
	for (i=j; --i>=0;)
	{
		bf->p1[i] = ((Point2*)p)[i].x;
		bf->p2[i] = ((Point2*)p)[i].y;
	}
	jb_free_null((void**)&p);
	fclose(file);
	goto exit0;

/* NOT USED
type2ni:
	if (position)
	{
		boundary_flow_error(bf,gettext("Unknow type"));
		goto exit2;
	}
	goto type2;

type2i:
	if (!position)
	{
		boundary_flow_error(bf,gettext("Unknow type"));
		goto exit1;
	}
*/

type2:
	xmlFree(buffer);
	file=jb_xml_node_get_content_file(node,&buffer);
	if (!file)
	{
		boundary_flow_error(bf,gettext("Not enough memory"));
		goto exit1;
	}
	j=-1;
	p=0;
	do
	{
		i=fscanf(file,FRF FRF,&x,&y);
		if (i<2) break;
		++j;
		p = (Point2*)g_try_realloc(p, (j + 1) * sizeof(Point2));
		if (!p)
		{
			boundary_flow_error(bf,gettext("Not enough memory"));
			goto exit4;
		}
		point2_open(((Point2*)p)+j,x,y);
	}
	while (1);
	bf->n = j;
	++j;
	bf->p1 = (JBFLOAT*)g_try_malloc(j * 2 *sizeof(JBFLOAT));
	if (!bf->p1)
	{
		boundary_flow_error(bf,gettext("Not enough memory"));
		goto exit4;
	}
	bf->p2 = bf->p1 + j;
	for (i=j; --i>=0;)
	{
		bf->p1[i] = ((Point2*)p)[i].x;
		bf->p2[i] = ((Point2*)p)[i].y;
	}
	jb_free_null((void**)&p);
	fclose(file);
	goto exit0;

type02i:
	if (!position)
	{
		boundary_flow_error(bf,gettext("Unknow type"));
		goto exit2;
	}
	if (i!=1 || j!=1)
	{
		boundary_flow_error(bf,gettext("Bad defined"));
		goto exit2;
	}
	bf->p1 = (JBFLOAT*)g_try_malloc(3 * sizeof(JBFLOAT));
	if (!bf->p1)
	{
		boundary_flow_error(bf,gettext("Not enough memory"));
		goto exit2;
	}
	bf->p2 = bf->p1 + 1;
	bf->p3 = bf->p2 + 1;
	bf->p1[0] = 0.;
	bf->p2[0] = x;
	bf->p3[0] = y;
	bf->n = 0;
	goto exit0;

type01i:
	if (!position)
	{
		boundary_flow_error(bf,gettext("Unknow type"));
		goto exit2;
	}

type01:
	if (i!=1)
	{
		boundary_flow_error(bf,gettext("Bad defined"));
		goto exit2;
	}
	bf->p1 = (JBFLOAT*)g_try_malloc(2 * sizeof(JBFLOAT));
	if (!bf->p1)
	{
		boundary_flow_error(bf,gettext("Not enough memory"));
		goto exit2;
	}
	bf->p2 = bf->p1 + 1;
	bf->p1[0] = 0.;
	bf->p2[0] = x;
	bf->n = 0;
	goto exit0;

type0i:
	if (!position)
	{
		boundary_flow_error(bf,gettext("Unknow type"));
		goto exit2;
	}

exit0:
	#if DEBUG_BOUNDARY_FLOW_OPEN_XML
		boundary_flow_print(bf,stderr);
		fprintf(stderr,"boundary_flow_open_xml: end\n");
	#endif
	xmlFree(buffer);
	return 1;

exit4:
	g_free(p);
	fclose(file);

exit2:
	xmlFree(buffer);

exit1:
	boundary_flow_delete(bf);
	#if DEBUG_BOUNDARY_FLOW_OPEN_XML
		fprintf(stderr,"boundary_flow_open_xml: end\n");
	#endif
	return 0;
}

#if INLINE_BOUNDARY_FLOW_OPEN_XML
	#define boundary_flow_open_xml _boundary_flow_open_xml
#else
	int boundary_flow_open_xml(BoundaryFlow*,xmlNode*,int);
#endif

static inline void _boundary_flow_save_xml
	(BoundaryFlow *bf,xmlNode *node,int position)
{
	int i;
	char *buffer,*buffer2,str[JB_BUFFER_SIZE];
	const xmlChar *bftype[]={XML_Q,XML_H,XML_Z,XML_Q_H,XML_Q_Z,XML_QT,
		XML_HT,XML_ZT,XML_QT_HT,XML_QT_ZT,XML_QH,XML_QZ,XML_SUPERCRITICAL,
		XML_DAM,XML_PIPE,XML_JUNCTION,XML_GAUGE};
	xmlNode *child;

	#if DEBUG_BOUNDARY_FLOW_SAVE_XML
		fprintf(stderr,"boundary_flow_save_xml: start\n");
		boundary_flow_print(bf,stderr);
	#endif

	buffer=NULL;

	if (position==0)
	{
		xmlSetProp(node,XML_NAME,(const xmlChar*)bf->name);
		jb_xml_node_set_int(node,XML_INITIAL,bf->pos);
		jb_xml_node_set_int(node,XML_FINAL,bf->pos2);
	}
	xmlSetProp(node,XML_TYPE,bftype[bf->type]);

	switch (bf->type)
	{
	case BOUNDARY_FLOW_Q_H:
		jb_xml_node_set_float(node,XML_DEPTH,bf->p3[0]);
	case BOUNDARY_FLOW_Q:
		jb_xml_node_set_float(node,XML_DISCHARGE,bf->p2[0]);
		break;
	case BOUNDARY_FLOW_H:
		jb_xml_node_set_float(node,XML_DEPTH,bf->p2[0]);
		break;
	case BOUNDARY_FLOW_Z:
		jb_xml_node_set_float(node,XML_LEVEL,bf->p2[0]);
		break;
	case BOUNDARY_FLOW_Q_Z:
		jb_xml_node_set_float(node,XML_DISCHARGE,bf->p2[0]);
		jb_xml_node_set_float(node,XML_LEVEL,bf->p3[0]);
		break;
	case BOUNDARY_FLOW_DAM:
		jb_xml_node_set_float(node,XML_LEVEL,DAM_LEVEL(bf));
		jb_xml_node_set_float(node,XML_ROUGHNESS,DAM_ROUGHNESS(bf));
	case BOUNDARY_FLOW_QT:
	case BOUNDARY_FLOW_QH:
	case BOUNDARY_FLOW_QZ:
	case BOUNDARY_FLOW_HT:
	case BOUNDARY_FLOW_ZT:
	case BOUNDARY_FLOW_PIPE:
		for (i=0; i<=bf->n; ++i)
		{
			snprintf(str,JB_BUFFER_SIZE,"\n    "FWF2 FWF,bf->p1[i],bf->p2[i]);
			if (!i) buffer2=g_strdup(str);
			else buffer2=g_strconcat(buffer,str,NULL);
			g_free(buffer);
			buffer=buffer2;
		}
		buffer2=g_strconcat(buffer,"\n  ",NULL);
		xmlNodeSetContent(node,(const xmlChar*)buffer2);
		g_free(buffer);
		g_free(buffer2);
		break;
	case BOUNDARY_FLOW_QT_HT:
	case BOUNDARY_FLOW_QT_ZT:
		for (i=0; i<=bf->n; ++i)
		{
			snprintf(str,JB_BUFFER_SIZE,"\n    "FWF2 FWF2 FWF,
				bf->p1[i],bf->p2[i],bf->p3[i]);
			if (!i) buffer2=g_strdup(str);
			else buffer2=g_strconcat(buffer,str,NULL);
			g_free(buffer);
			buffer=buffer2;
		}
		buffer2=g_strconcat(buffer,"\n  ",NULL);
		xmlNodeSetContent(node,(const xmlChar*)buffer2);
		g_free(buffer);
		g_free(buffer2);
		break;
	case BOUNDARY_FLOW_JUNCTION:
		for (i=0; i<=JUNCTION_N(bf); ++i)
		{
			child=xmlNewChild(node,0,XML_JUNCTION,0);
			junction_data_save_xml(JUNCTION_DATA(bf,i),child);
		}
		break;
	case BOUNDARY_FLOW_GAUGE:
		if (GAUGE_TOLERANCE(bf)>0.)
			jb_xml_node_set_float(node,XML_TOLERANCE,GAUGE_TOLERANCE(bf));
		for (i=0; i<=bf->n; ++i)
		{
			snprintf(str,JB_BUFFER_SIZE,"\n    "FWF2 FWF,bf->p1[i],bf->p2[i]);
			if (!i) buffer2=g_strdup(str);
			else buffer2=g_strconcat(buffer,str,NULL);
			g_free(buffer);
			buffer=buffer2;
		}
		buffer2=g_strconcat(buffer,"\n  ",NULL);
		xmlNodeSetContent(node,(const xmlChar*)buffer2);
		g_free(buffer);
		g_free(buffer2);
	}

	#if DEBUG_BOUNDARY_FLOW_SAVE_XML
		fprintf(stderr,"boundary_flow_save_xml: end\n");
	#endif
}

#if INLINE_BOUNDARY_FLOW_SAVE_XML
	#define boundary_flow_save_xml _boundary_flow_save_xml
#else
	void boundary_flow_save_xml(BoundaryFlow*,xmlNode*,int);
#endif

static inline JBDOUBLE _boundary_flow_parameter(BoundaryFlow *bf,JBDOUBLE t)
{
	register JBDOUBLE k;
	#if DEBUG_BOUNDARY_FLOW_PARAMETER
		int i;
		fprintf(stderr,"boundary_flow_parameter: start\n");
		fprintf(stderr,"BFP t="FWL"\n",t);
		for (i=0; i<=bf->n; ++i) fprintf(stderr,"BFP i=%d p1="FWF" p2="FWF"\n",
			i,bf->p1[i],bf->p2[i]);
	#endif
	switch (bf->type)
	{
	case BOUNDARY_FLOW_QT:
	case BOUNDARY_FLOW_HT:
	case BOUNDARY_FLOW_ZT:
	case BOUNDARY_FLOW_QT_HT:
	case BOUNDARY_FLOW_QT_ZT:
		if (!simulating) return bf->p2[0];
	}
	k = jbm_farray_interpolate(t, bf->p1, bf->p2, bf->n);
	#if DEBUG_BOUNDARY_FLOW_PARAMETER
		fprintf(stderr,"boundary_flow_parameter: end\n");
	#endif
	return k;
}

#if INLINE_BOUNDARY_FLOW_PARAMETER
	#define boundary_flow_parameter _boundary_flow_parameter
#else
	JBDOUBLE boundary_flow_parameter(BoundaryFlow*,JBDOUBLE);
#endif

static inline JBDOUBLE _boundary_flow_parameter2(BoundaryFlow *bf,JBDOUBLE t)
{
	register JBDOUBLE k;
	#if DEBUG_BOUNDARY_FLOW_PARAMETER2
		int i;
		fprintf(stderr,"boundary_flow_parameter2: start\n");
		fprintf(stderr,"BFP2 t="FWL"\n",t);
		for (i=0; i<=bf->n; ++i) fprintf(stderr,"BFP2 i=%d p1="FWF" p3="FWF"\n",
			i,bf->p1[i],bf->p3[i]);
	#endif
	switch (bf->type)
	{
	case BOUNDARY_FLOW_QT:
	case BOUNDARY_FLOW_HT:
	case BOUNDARY_FLOW_ZT:
	case BOUNDARY_FLOW_QT_HT:
	case BOUNDARY_FLOW_QT_ZT:
		if (!simulating) return bf->p3[0];
	}
	k = jbm_farray_interpolate(t, bf->p1, bf->p3, bf->n);
	#if DEBUG_BOUNDARY_FLOW_PARAMETER2
		fprintf(stderr,"boundary_flow_parameter2: end\n");
	#endif
	return k;
}

#if INLINE_BOUNDARY_FLOW_PARAMETER2
	#define boundary_flow_parameter2 \
		_boundary_flow_parameter2
#else
	JBDOUBLE boundary_flow_parameter2(BoundaryFlow*,JBDOUBLE);
#endif

static inline JBDOUBLE _boundary_flow_parameter_integral
	(BoundaryFlow *bf,JBDOUBLE t,JBDOUBLE tmax)
{
	register JBDOUBLE k;
	#if DEBUG_BOUNDARY_FLOW_PARAMETER_INTEGRAL
		int i;
		fprintf(stderr,"boundary_flow_parameter_integral: start\n");
		fprintf(stderr,"BFPI t="FWL" tmax="FWL"\n",t,tmax);
		for (i=0; i<=bf->n; ++i) fprintf(stderr,"BFPI i=%d p1="FWF" p2="FWF"\n",
			i,bf->p1[i],bf->p2[i]);
	#endif
	switch (bf->type)
	{
	case BOUNDARY_FLOW_QT:
	case BOUNDARY_FLOW_HT:
	case BOUNDARY_FLOW_ZT:
	case BOUNDARY_FLOW_QT_HT:
	case BOUNDARY_FLOW_QT_ZT:
		if (!simulating) return bf->p2[0] * (tmax - t);
	}
	k = jbm_farray_integral(bf->p1, bf->p2, bf->n, t, tmax);
	#if DEBUG_BOUNDARY_FLOW_PARAMETER_INTEGRAL
		fprintf(stderr,"boundary_flow_parameter_integral: end\n");
	#endif
	return k;
}

#if INLINE_BOUNDARY_FLOW_PARAMETER_INTEGRAL
	#define boundary_flow_parameter_integral _boundary_flow_parameter_integral
#else
	JBDOUBLE boundary_flow_parameter_integral(BoundaryFlow*,JBDOUBLE,JBDOUBLE);
#endif

#endif
