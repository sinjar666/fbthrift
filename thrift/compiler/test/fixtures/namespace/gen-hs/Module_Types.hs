{-# LANGUAGE DeriveDataTypeable #-}
{-# LANGUAGE OverloadedStrings #-}
{-# OPTIONS_GHC -fno-warn-missing-fields #-}
{-# OPTIONS_GHC -fno-warn-missing-signatures #-}
{-# OPTIONS_GHC -fno-warn-name-shadowing #-}
{-# OPTIONS_GHC -fno-warn-unused-imports #-}
{-# OPTIONS_GHC -fno-warn-unused-matches #-}

-----------------------------------------------------------------
-- Autogenerated by Thrift
--                                                             --
-- DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
--  @generated
-----------------------------------------------------------------

module Module_Types where
import Prelude ( Bool(..), Enum, Float, IO, Double, String, Maybe(..),
                 Eq, Show, Ord,
                 concat, error, fromIntegral, fromEnum, length, map,
                 maybe, not, null, otherwise, return, show, toEnum,
                 enumFromTo, Bounded, minBound, maxBound, seq,
                 (.), (&&), (||), (==), (++), ($), (-), (>>=), (>>))

import qualified Control.Applicative as Applicative (ZipList(..))
import Control.Applicative ( (<*>) )
import qualified Control.DeepSeq as DeepSeq
import qualified Control.Exception as Exception
import qualified Control.Monad as Monad ( liftM, ap, when )
import qualified Data.ByteString.Lazy as BS
import Data.Functor ( (<$>) )
import qualified Data.Hashable as Hashable
import qualified Data.Int as Int
import qualified Data.Maybe as Maybe (catMaybes)
import qualified Data.Text.Lazy.Encoding as Encoding ( decodeUtf8, encodeUtf8 )
import qualified Data.Text.Lazy as LT
import qualified Data.Typeable as Typeable ( Typeable )
import qualified Data.HashMap.Strict as Map
import qualified Data.HashSet as Set
import qualified Data.Vector as Vector
import qualified Test.QuickCheck.Arbitrary as Arbitrary ( Arbitrary(..) )
import qualified Test.QuickCheck as QuickCheck ( elements )

import qualified Thrift
import qualified Thrift.Types as Types
import qualified Thrift.Serializable as Serializable
import qualified Thrift.Arbitraries as Arbitraries


data Foo = Foo
  { foo_MyInt :: Int.Int64
  } deriving (Show,Eq,Typeable.Typeable)
instance Serializable.ThriftSerializable Foo where
  encode = encode_Foo
  decode = decode_Foo
instance Hashable.Hashable Foo where
  hashWithSalt salt record = salt   `Hashable.hashWithSalt` foo_MyInt record  
instance DeepSeq.NFData Foo where
  rnf _record0 =
    DeepSeq.rnf (foo_MyInt _record0) `seq`
    ()
instance Arbitrary.Arbitrary Foo where 
  arbitrary = Monad.liftM Foo (Arbitrary.arbitrary)
  shrink obj | obj == default_Foo = []
             | otherwise = Maybe.catMaybes
    [ if obj == default_Foo{foo_MyInt = foo_MyInt obj} then Nothing else Just $ default_Foo{foo_MyInt = foo_MyInt obj}
    ]
from_Foo :: Foo -> Types.ThriftVal
from_Foo record = Types.TStruct $ Map.fromList $ Maybe.catMaybes
  [ (\_v3 -> Just (1, ("MyInt",Types.TI64 _v3))) $ foo_MyInt record
  ]
write_Foo :: (Thrift.Protocol p, Thrift.Transport t) => p t -> Foo -> IO ()
write_Foo oprot record = Thrift.writeVal oprot $ from_Foo record
encode_Foo :: (Thrift.Protocol p, Thrift.Transport t) => p t -> Foo -> BS.ByteString
encode_Foo oprot record = Thrift.serializeVal oprot $ from_Foo record
to_Foo :: Types.ThriftVal -> Foo
to_Foo (Types.TStruct fields) = Foo{
  foo_MyInt = maybe (foo_MyInt default_Foo) (\(_,_val5) -> (case _val5 of {Types.TI64 _val6 -> _val6; _ -> error "wrong type"})) (Map.lookup (1) fields)
  }
to_Foo _ = error "not a struct"
read_Foo :: (Thrift.Transport t, Thrift.Protocol p) => p t -> IO Foo
read_Foo iprot = to_Foo <$> Thrift.readVal iprot (Types.T_STRUCT typemap_Foo)
decode_Foo :: (Thrift.Protocol p, Thrift.Transport t) => p t -> BS.ByteString -> Foo
decode_Foo iprot bs = to_Foo $ Thrift.deserializeVal iprot (Types.T_STRUCT typemap_Foo) bs
typemap_Foo :: Types.TypeMap
typemap_Foo = Map.fromList [("MyInt",(1,Types.T_I64))]
default_Foo :: Foo
default_Foo = Foo{
  foo_MyInt = 0}
