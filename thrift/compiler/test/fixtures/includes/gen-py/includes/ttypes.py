#
# Autogenerated by Thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#

from __future__ import absolute_import
import six
from thrift.util.Recursive import fix_spec
from thrift.Thrift import *
from thrift.protocol.TProtocol import TProtocolException



import pprint
import warnings
from thrift import Thrift
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.protocol import TCompactProtocol
from thrift.protocol import THeaderProtocol
try:
  from thrift.protocol import fastbinary
  if fastbinary.version < 2:
    fastbinary = None
    warnings.warn("Disabling fastbinary, need at least version 2")
except:
  fastbinary = None
try:
  from thrift.protocol import fastproto
except:
  fastproto = None
all_structs = []
UTF8STRINGS = bool(0) or sys.version_info.major >= 3

class Included:
  """
  Attributes:
   - MyIntField
  """

  thrift_spec = None
  thrift_field_annotations = None
  thrift_struct_annotations = None
  __init__ = None
  @staticmethod
  def isUnion():
    return False

  def read(self, iprot):
    if (iprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated or (iprot.__class__ == THeaderProtocol.THeaderProtocol and iprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_BINARY_PROTOCOL)) and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastbinary is not None:
      fastbinary.decode_binary(self, iprot.trans, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS)
      return
    if (iprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated or (iprot.__class__ == THeaderProtocol.THeaderProtocol and iprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_BINARY_PROTOCOL)) and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastproto is not None:
      fastproto.decode(self, iprot.trans, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS, protoid=0)
      return
    if (iprot.__class__ == TCompactProtocol.TCompactProtocolAccelerated or (iprot.__class__ == THeaderProtocol.THeaderProtocol and iprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_COMPACT_PROTOCOL)) and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None and fastproto is not None:
      fastproto.decode(self, iprot.trans, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS, protoid=2)
      return
    iprot.readStructBegin()
    while True:
      (fname, ftype, fid) = iprot.readFieldBegin()
      if ftype == TType.STOP:
        break
      if fid == 1:
        if ftype == TType.I64:
          self.MyIntField = iprot.readI64()
        else:
          iprot.skip(ftype)
      else:
        iprot.skip(ftype)
      iprot.readFieldEnd()
    iprot.readStructEnd()

  def write(self, oprot):
    if (oprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated or (oprot.__class__ == THeaderProtocol.THeaderProtocol and oprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_BINARY_PROTOCOL)) and self.thrift_spec is not None and fastbinary is not None:
      oprot.trans.write(fastbinary.encode_binary(self, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS))
      return
    if (oprot.__class__ == TBinaryProtocol.TBinaryProtocolAccelerated or (oprot.__class__ == THeaderProtocol.THeaderProtocol and oprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_BINARY_PROTOCOL)) and self.thrift_spec is not None and fastproto is not None:
      oprot.trans.write(fastproto.encode(self, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS, protoid=0))
      return
    if (oprot.__class__ == TCompactProtocol.TCompactProtocolAccelerated or (oprot.__class__ == THeaderProtocol.THeaderProtocol and oprot.get_protocol_id() == THeaderProtocol.THeaderProtocol.T_COMPACT_PROTOCOL)) and self.thrift_spec is not None and fastproto is not None:
      oprot.trans.write(fastproto.encode(self, [self.__class__, self.thrift_spec, False], utf8strings=UTF8STRINGS, protoid=2))
      return
    oprot.writeStructBegin('Included')
    if self.MyIntField != None:
      oprot.writeFieldBegin('MyIntField', TType.I64, 1)
      oprot.writeI64(self.MyIntField)
      oprot.writeFieldEnd()
    oprot.writeFieldStop()
    oprot.writeStructEnd()

  def __repr__(self):
    L = []
    for key, value in six.iteritems(self.__dict__):
      padding = ' ' * (len(key) + 1)
      value = pprint.pformat(value)
      value = padding.join(value.splitlines(True))
      L.append('    %s=%s' % (key, value))
    return "%s(\n%s)" % (self.__class__.__name__, ",\n".join(L))

  def __eq__(self, other):
    if not isinstance(other, self.__class__):
      return False

    return self.__dict__ == other.__dict__ 

  def __ne__(self, other):
    return not (self == other)

all_structs.append(Included)
Included.thrift_spec = (
  None, # 0
  (1, TType.I64, 'MyIntField', None, 0, 2, ), # 1
)

Included.thrift_struct_annotations = {
}
Included.thrift_field_annotations = {
}

def Included__init__(self, MyIntField=Included.thrift_spec[1][4],):
  self.MyIntField = MyIntField

Included.__init__ = Included__init__

fix_spec(all_structs)
del all_structs
