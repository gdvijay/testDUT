#include "DIA_AVP.h"

DIA_ParseCode DIA_AVP::get_next_sub_avp(DIA_AVP& avp)
{
  if (AVP_DATA_TYPE_GROUPED != m_datatype)
  {
    return DIA_ERR_FAILURE;
  }

  return DIA_PARSE_CODE_SUCESS;


}
