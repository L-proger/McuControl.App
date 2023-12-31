#pragma once
//imported type: ILink from module: MicroNetwork.User
//imported type: void from module: LanguagePrimitive
#include <MicroNetwork.User.h>
namespace McuControl{
    class IMcuControl;
} //McuControl
namespace LFramework{
    //Interface ABI
    template<>
    struct InterfaceAbi<McuControl::IMcuControl> : public InterfaceAbi<MicroNetwork::User::ILink>{
        using Base = InterfaceAbi<MicroNetwork::User::ILink>;
        //{452b9fce-5f9b-4a40-a4e3-cac1435af2df}
        static constexpr InterfaceID ID() { return { 0x452b9fce, 0x4a405f9b, 0xc1cae3a4, 0xdff25a43 }; }
        virtual Result LFRAMEWORK_COM_CALL readMemory() = 0;
    private:
        ~InterfaceAbi() = delete;
    }; //IMcuControl
    //Interface Remap
    template<class TImplementer>
    struct InterfaceRemap<McuControl::IMcuControl, TImplementer> : public InterfaceRemap<MicroNetwork::User::ILink, TImplementer>{
        virtual Result LFRAMEWORK_COM_CALL readMemory(){
            try{
                this->implementer()->readMemory();
            }
            catch(...){
                return LFramework::Result::UnknownFailure;
            }
            return LFramework::Result::Ok;
        }
    };
    //Interface Wrapper
    template<>
    class InterfaceWrapper<McuControl::IMcuControl> : public InterfaceWrapper<MicroNetwork::User::ILink> {
    public:
        void readMemory(){
            auto comCallResult = reinterpret_cast<InterfaceAbi<McuControl::IMcuControl>*>(_abi)->readMemory();
            if(comCallResult != Result::Ok){
                throw ComException(comCallResult);
            }
        }
    };
}

