/* soapClient.cpp
   Generated by gSOAP 2.7.6c from hreport.h
   Copyright (C) 2000-2005, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.7.6c 2009-07-08 09:04:39 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__GetTemplate(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__GetTemplate *ns1__GetTemplate, _ns1__GetTemplateResponse *ns1__GetTemplateResponse)
{	struct __ns1__GetTemplate soap_tmp___ns1__GetTemplate;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.103.21/hreportservice/hreport.asmx";
	if (!soap_action)
		soap_action = "http://192.168.103.21/hreportservice/GetTemplate";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__GetTemplate.ns1__GetTemplate = ns1__GetTemplate;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__GetTemplate(soap, &soap_tmp___ns1__GetTemplate);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__GetTemplate(soap, &soap_tmp___ns1__GetTemplate, "-ns1:GetTemplate", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__GetTemplate(soap, &soap_tmp___ns1__GetTemplate, "-ns1:GetTemplate", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__GetTemplateResponse)
		return soap_closesock(soap);
	ns1__GetTemplateResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__GetTemplateResponse->soap_get(soap, "ns1:GetTemplateResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__GetTemplateConfig(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__GetTemplateConfig *ns1__GetTemplateConfig, _ns1__GetTemplateConfigResponse *ns1__GetTemplateConfigResponse)
{	struct __ns1__GetTemplateConfig soap_tmp___ns1__GetTemplateConfig;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.103.21/hreportservice/hreport.asmx";
	if (!soap_action)
		soap_action = "http://192.168.103.21/hreportservice/GetTemplateConfig";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__GetTemplateConfig.ns1__GetTemplateConfig = ns1__GetTemplateConfig;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__GetTemplateConfig(soap, &soap_tmp___ns1__GetTemplateConfig);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__GetTemplateConfig(soap, &soap_tmp___ns1__GetTemplateConfig, "-ns1:GetTemplateConfig", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__GetTemplateConfig(soap, &soap_tmp___ns1__GetTemplateConfig, "-ns1:GetTemplateConfig", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__GetTemplateConfigResponse)
		return soap_closesock(soap);
	ns1__GetTemplateConfigResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__GetTemplateConfigResponse->soap_get(soap, "ns1:GetTemplateConfigResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__Query(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__Query *ns1__Query, _ns1__QueryResponse *ns1__QueryResponse)
{	struct __ns1__Query soap_tmp___ns1__Query;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.103.21/hreportservice/hreport.asmx";
	if (!soap_action)
		soap_action = "http://192.168.103.21/hreportservice/Query";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__Query.ns1__Query = ns1__Query;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__Query(soap, &soap_tmp___ns1__Query);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__Query(soap, &soap_tmp___ns1__Query, "-ns1:Query", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__Query(soap, &soap_tmp___ns1__Query, "-ns1:Query", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__QueryResponse)
		return soap_closesock(soap);
	ns1__QueryResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__QueryResponse->soap_get(soap, "ns1:QueryResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__GetTemplateTree(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__GetTemplateTree *ns1__GetTemplateTree, _ns1__GetTemplateTreeResponse *ns1__GetTemplateTreeResponse)
{	struct __ns1__GetTemplateTree soap_tmp___ns1__GetTemplateTree;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.103.21/hreportservice/hreport.asmx";
	if (!soap_action)
		soap_action = "http://192.168.103.21/hreportservice/GetTemplateTree";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__GetTemplateTree.ns1__GetTemplateTree = ns1__GetTemplateTree;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__GetTemplateTree(soap, &soap_tmp___ns1__GetTemplateTree);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__GetTemplateTree(soap, &soap_tmp___ns1__GetTemplateTree, "-ns1:GetTemplateTree", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__GetTemplateTree(soap, &soap_tmp___ns1__GetTemplateTree, "-ns1:GetTemplateTree", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__GetTemplateTreeResponse)
		return soap_closesock(soap);
	ns1__GetTemplateTreeResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__GetTemplateTreeResponse->soap_get(soap, "ns1:GetTemplateTreeResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__GetTemplateInformation(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__GetTemplateInformation *ns1__GetTemplateInformation, _ns1__GetTemplateInformationResponse *ns1__GetTemplateInformationResponse)
{	struct __ns1__GetTemplateInformation soap_tmp___ns1__GetTemplateInformation;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.103.21/hreportservice/hreport.asmx";
	if (!soap_action)
		soap_action = "http://192.168.103.21/hreportservice/GetTemplateInformation";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__GetTemplateInformation.ns1__GetTemplateInformation = ns1__GetTemplateInformation;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__GetTemplateInformation(soap, &soap_tmp___ns1__GetTemplateInformation);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__GetTemplateInformation(soap, &soap_tmp___ns1__GetTemplateInformation, "-ns1:GetTemplateInformation", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__GetTemplateInformation(soap, &soap_tmp___ns1__GetTemplateInformation, "-ns1:GetTemplateInformation", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__GetTemplateInformationResponse)
		return soap_closesock(soap);
	ns1__GetTemplateInformationResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__GetTemplateInformationResponse->soap_get(soap, "ns1:GetTemplateInformationResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__GetTemplate_(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__GetTemplate *ns1__GetTemplate, _ns1__GetTemplateResponse *ns1__GetTemplateResponse)
{	struct __ns1__GetTemplate_ soap_tmp___ns1__GetTemplate_;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.103.21/hreportservice/hreport.asmx";
	if (!soap_action)
		soap_action = "http://192.168.103.21/hreportservice/GetTemplate";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__GetTemplate_.ns1__GetTemplate = ns1__GetTemplate;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__GetTemplate_(soap, &soap_tmp___ns1__GetTemplate_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__GetTemplate_(soap, &soap_tmp___ns1__GetTemplate_, "-ns1:GetTemplate", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__GetTemplate_(soap, &soap_tmp___ns1__GetTemplate_, "-ns1:GetTemplate", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__GetTemplateResponse)
		return soap_closesock(soap);
	ns1__GetTemplateResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__GetTemplateResponse->soap_get(soap, "ns1:GetTemplateResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__GetTemplateConfig_(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__GetTemplateConfig *ns1__GetTemplateConfig, _ns1__GetTemplateConfigResponse *ns1__GetTemplateConfigResponse)
{	struct __ns1__GetTemplateConfig_ soap_tmp___ns1__GetTemplateConfig_;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.103.21/hreportservice/hreport.asmx";
	if (!soap_action)
		soap_action = "http://192.168.103.21/hreportservice/GetTemplateConfig";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__GetTemplateConfig_.ns1__GetTemplateConfig = ns1__GetTemplateConfig;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__GetTemplateConfig_(soap, &soap_tmp___ns1__GetTemplateConfig_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__GetTemplateConfig_(soap, &soap_tmp___ns1__GetTemplateConfig_, "-ns1:GetTemplateConfig", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__GetTemplateConfig_(soap, &soap_tmp___ns1__GetTemplateConfig_, "-ns1:GetTemplateConfig", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__GetTemplateConfigResponse)
		return soap_closesock(soap);
	ns1__GetTemplateConfigResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__GetTemplateConfigResponse->soap_get(soap, "ns1:GetTemplateConfigResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__Query_(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__Query *ns1__Query, _ns1__QueryResponse *ns1__QueryResponse)
{	struct __ns1__Query_ soap_tmp___ns1__Query_;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.103.21/hreportservice/hreport.asmx";
	if (!soap_action)
		soap_action = "http://192.168.103.21/hreportservice/Query";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__Query_.ns1__Query = ns1__Query;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__Query_(soap, &soap_tmp___ns1__Query_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__Query_(soap, &soap_tmp___ns1__Query_, "-ns1:Query", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__Query_(soap, &soap_tmp___ns1__Query_, "-ns1:Query", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__QueryResponse)
		return soap_closesock(soap);
	ns1__QueryResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__QueryResponse->soap_get(soap, "ns1:QueryResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__GetTemplateTree_(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__GetTemplateTree *ns1__GetTemplateTree, _ns1__GetTemplateTreeResponse *ns1__GetTemplateTreeResponse)
{	struct __ns1__GetTemplateTree_ soap_tmp___ns1__GetTemplateTree_;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.103.21/hreportservice/hreport.asmx";
	if (!soap_action)
		soap_action = "http://192.168.103.21/hreportservice/GetTemplateTree";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__GetTemplateTree_.ns1__GetTemplateTree = ns1__GetTemplateTree;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__GetTemplateTree_(soap, &soap_tmp___ns1__GetTemplateTree_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__GetTemplateTree_(soap, &soap_tmp___ns1__GetTemplateTree_, "-ns1:GetTemplateTree", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__GetTemplateTree_(soap, &soap_tmp___ns1__GetTemplateTree_, "-ns1:GetTemplateTree", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__GetTemplateTreeResponse)
		return soap_closesock(soap);
	ns1__GetTemplateTreeResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__GetTemplateTreeResponse->soap_get(soap, "ns1:GetTemplateTreeResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__GetTemplateInformation_(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__GetTemplateInformation *ns1__GetTemplateInformation, _ns1__GetTemplateInformationResponse *ns1__GetTemplateInformationResponse)
{	struct __ns1__GetTemplateInformation_ soap_tmp___ns1__GetTemplateInformation_;
	if (!soap_endpoint)
		soap_endpoint = "http://192.168.103.21/hreportservice/hreport.asmx";
	if (!soap_action)
		soap_action = "http://192.168.103.21/hreportservice/GetTemplateInformation";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__GetTemplateInformation_.ns1__GetTemplateInformation = ns1__GetTemplateInformation;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__GetTemplateInformation_(soap, &soap_tmp___ns1__GetTemplateInformation_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__GetTemplateInformation_(soap, &soap_tmp___ns1__GetTemplateInformation_, "-ns1:GetTemplateInformation", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__GetTemplateInformation_(soap, &soap_tmp___ns1__GetTemplateInformation_, "-ns1:GetTemplateInformation", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__GetTemplateInformationResponse)
		return soap_closesock(soap);
	ns1__GetTemplateInformationResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__GetTemplateInformationResponse->soap_get(soap, "ns1:GetTemplateInformationResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

/* End of soapClient.cpp */
