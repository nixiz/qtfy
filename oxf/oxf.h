#ifndef OXF_H_
#define OXF_H_

#include <QMutex>
#include <QString>
#include "qtfy.hpp"

#ifdef USE_OLD_VERSION
template <typename Interface>
struct InterfaceTraits
{
    static const QString name;
    //static const QStringRef getIdentifier()
    //{
    //    static const QString idenName = QString("%1Portu").arg(name.mid(1));
    //    qDebug() << "create identifier name: " << idenName;
    //    return QStringRef(&idenName);
    //}
};
template <typename Interface>
const QString InterfaceTraits<Interface>::name = QString("unknown-type");

// register EmptyInterface type for correct derivation of not registered types
template <> const QString InterfaceTraits<EmptyInterface>::name = QString("EI");

#define SAVE_INTERFACE(Interface)   \
template <> const QString InterfaceTraits<Interface>::name = #Interface
#else
#define SAVE_INTERFACE(Interface)
#endif

typedef QMutex OMOSMutex;

class OMOSFactory {
    OMOSFactory() {}
public:
    ~OMOSFactory() {}
    static OMOSFactory* instance()
    {
        static OMOSFactory _ins;
        return &_ins;
    }

    OMOSMutex* createOMOSMutex(QMutex::RecursionMode mode = QMutex::NonRecursive)
    {
        return new OMOSMutex(mode);
    }
private:
    OMOSFactory(const OMOSFactory&);
};

template <class T>
struct isThreadObj
{
    static const bool value;
};
template <class T>
const bool isThreadObj<T>::value = false;

namespace OXF {

inline bool initialize()
{
    return true;
}

inline void start(bool) {}
inline void end() {}

}

#endif
