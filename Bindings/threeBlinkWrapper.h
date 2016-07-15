#ifndef THREE_BLINK_WRAPPER_H
#define THREE_BLINK_WRAPPER_H

#include "bindings/core/v8/ScriptWrappable.h"
#include "platform/heap/Handle.h"
#include "wtf/Vector.h"
#include "wtf/HashMap.h"
#include "wtf/text/StringHash.h"

//Let

namespace blink {


class threeBlinkWrapper;

class threeBlinkWrapperRepo
{

   public:
       static void setWrapperImplPair(void* implPtr, threeBlinkWrapper* pWrapper)
        {
            m_repoMap.set(implPtr, pWrapper);
        }

       static void* getWrapperForImpl(void* implPtr)
        {
            if(m_repoMap.contains(implPtr))
                return  m_repoMap.get(implPtr);
            else
                return NULL;
        }

       static void removeWrapperForImpl(void* implPtr)
        {
            m_repoMap.remove(implPtr);
        }

   private:

       static HashMap<void*, threeBlinkWrapper*> m_repoMap;
};


class threeBlinkWrapper : public RefCounted<threeBlinkWrapper>, public ScriptWrappable {

    DEFINE_WRAPPERTYPEINFO();

public:
    threeBlinkWrapper() {
        m_impl = NULL;
        m_isOwner = false;
     }
    virtual ~threeBlinkWrapper() {
        if(m_impl)
        {
            //m_impl->setWrapper(NULL);
            threeBlinkWrapperRepo::removeWrapperForImpl(m_impl);
            //if(m_isOwner)
            //   delete m_impl;
            delete m_impl;
        }
        m_impl = NULL;
     }

    void  setImpl(void* impl) {
        m_impl = impl;
        //if(m_impl != NULL)
        //{
        //    m_impl->setWrapper((void*)this);
        //}
        threeBlinkWrapperRepo::setWrapperImplPair(m_impl, this); //the` map is for looking for
     }


    void* getImpl()           { return m_impl; }

    void setRef(String name, threeBlinkWrapper* pObj) {
        if(!m_refedWrappersMap.contains(name))
            m_refedWrappersMap.set(name, pObj); //Incerate reffernces by Refpr
    }
    void removeRef(String name) {
        if(m_refedWrappersMap.contains(name))
            m_refedWrappersMap.remove(name);   //Decreate references
    }

    void setRef(threeBlinkWrapper* pObj) {
        if(!m_refedWrappersVector.contains(pObj))
            m_refedWrappersVector.append(pObj);
    }
    void removeRef(threeBlinkWrapper* pObj) {
        if(m_refedWrappersVector.contains(pObj))
            m_refedWrappersVector.remove(m_refedWrappersVector.find(pObj));
    }

protected:
    three:: baseObj* m_impl; // Should  the implementation also  refcounted? as in COCOS2D?

    HashMap<String, RefPtr<threeBlinkWrapper>> m_refedWrappersMap;
    Vector<RefPtr<threeBlinkWrapper>> m_refedWrappersVector;

};



}

#endif
