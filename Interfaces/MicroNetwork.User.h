#pragma once
//imported type: LFramework::IUnknown from module: LFramework/COM/ComObject.h
//imported type: bool from module: LanguagePrimitive
#include <LFramework/COM/ComObject.h>
namespace MicroNetwork::User{
    class ILink;
} //MicroNetwork::User
namespace LFramework{
    //Interface ABI
    template<>
    struct InterfaceAbi<MicroNetwork::User::ILink> : public InterfaceAbi<LFramework::IUnknown>{
        using Base = InterfaceAbi<LFramework::IUnknown>;
        //{e25b1fdb-a29a-48a2-9826-4be290a546e9}
        static constexpr InterfaceID ID() { return { 0xe25b1fdb, 0x48a2a29a, 0xe24b2698, 0xe946a590 }; }
        virtual Result LFRAMEWORK_COM_CALL isConnected(bool& result) = 0;
    private:
        ~InterfaceAbi() = delete;
    }; //ILink
    //Interface Remap
    template<class TImplementer>
    struct InterfaceRemap<MicroNetwork::User::ILink, TImplementer> : public InterfaceRemap<LFramework::IUnknown, TImplementer>{
        virtual Result LFRAMEWORK_COM_CALL isConnected(bool& result){
            try{
                result = this->implementer()->isConnected();
            }
            catch(...){
                return LFramework::Result::UnknownFailure;
            }
            return LFramework::Result::Ok;
        }
    };
    //Interface Wrapper
    template<>
    class InterfaceWrapper<MicroNetwork::User::ILink> : public InterfaceWrapper<LFramework::IUnknown> {
    public:
        bool isConnected(){
            bool result;
            auto comCallResult = reinterpret_cast<InterfaceAbi<MicroNetwork::User::ILink>*>(_abi)->isConnected(result);
            if(comCallResult != Result::Ok){
                throw ComException(comCallResult);
            }
            return result;
        }
    };
}

