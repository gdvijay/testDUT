#ifndef DIA_AVP_H
#define DIA_AVP_H

enum DIA_ParseCode
{
 DIA_PARSE_CODE_SUCESS,
 DIA_ERR_FAILURE
};

enum DIA_AvpDataType
{
 AVP_DATA_TYPE_DEFAULT = -1,
 AVP_DATA_TYPE_GROUPED,
 AVP_DATA_TYPE_OCTET_STRING
};

class DIA_AVP
{
  public:
  DIA_AvpDataType m_datatype; 
  DIA_ParseCode get_next_sub_avp(DIA_AVP& avp);     

};

#endif
