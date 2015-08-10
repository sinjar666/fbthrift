/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */


import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.facebook.thrift.lite.*;
import com.facebook.thrift.lite.protocol.*;


public class ModuleLogger {

  public final Module.EventType mEventType;

  private final Map<ThriftProperty<?>, Object> mMap = new HashMap<ThriftProperty<?>, Object>();

  public ModuleLogger(Module.EventType type) {
    mEventType = type;
  }

  public <T> ModuleLogger addProperty(ThriftProperty<T> property, T value) {
    mMap.put(property, value);
    return this;
  }

  public static <T> void writeFieldBegin(TBinaryProtocol oprot, ThriftProperty<T> field) throws IOException {
    TField tField = new TField(field.key, field.type, field.id);
    oprot.writeFieldBegin(tField);
  }

  public void write(TBinaryProtocol oprot) throws IOException {
    switch (mEventType) {
      case ComplexUnion: {
        if (this.mMap.size() < 1) {
          throw new TProtocolException(TProtocolException.MISSING_REQUIRED_FIELD, "Cannot write a union with no set value!");
        } else if (this.mMap.size() > 1) {
          throw new TProtocolException(TProtocolException.INVALID_DATA, "Cannot write a union with more than one set value!");
        }
        oprot.writeStructBegin(new TStruct("ComplexUnion"));
        switch (mMap.keySet().iterator().next().id) {
        case 1: {
          writeFieldBegin(oprot, Module.ComplexUnion_intValue);
          oprot.writeI64((long) mMap.get(Module.ComplexUnion_intValue));
          oprot.writeFieldEnd();
          break;
        }
      
        case 2: {
          writeFieldBegin(oprot, Module.ComplexUnion_stringValue);
          oprot.writeString((String) mMap.get(Module.ComplexUnion_stringValue));
          oprot.writeFieldEnd();
          break;
        }
      
        case 3: {
          writeFieldBegin(oprot, Module.ComplexUnion_intListValue);
          List<Long> var0 = (List<Long>) mMap.get(Module.ComplexUnion_intListValue);
          oprot.writeListBegin(new TList(TType.I64, var0.size()));
          for (long iter0 : var0) {
            oprot.writeI64(iter0);
          }
          oprot.writeListEnd();
          oprot.writeFieldEnd();
          break;
        }
      
        case 4: {
          writeFieldBegin(oprot, Module.ComplexUnion_stringListValue);
          List<String> var0 = (List<String>) mMap.get(Module.ComplexUnion_stringListValue);
          oprot.writeListBegin(new TList(TType.STRING, var0.size()));
          for (String iter0 : var0) {
            oprot.writeString(iter0);
          }
          oprot.writeListEnd();
          oprot.writeFieldEnd();
          break;
        }
      
        }
        oprot.writeFieldStop();
        oprot.writeStructEnd();
        break;
      }
      
      
    }
  }
}
