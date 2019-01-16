#ifndef LinkedList_HPP
#define LinkedList_HPP

#include <list>
#include <type_traits>
#include <functional>

#include <QDataStream>

#include "Core/Data/entitybase.hpp"

template<class TEntity>
class LinkedList
{
    static_assert(std::is_base_of<EntityBase, TEntity>::value, "TEntity must inherit from Entity");

public:
    LinkedList() { }
    virtual ~LinkedList() { }

    typedef std::function<bool(const TEntity &)> Predicate;

    virtual QVector<TEntity> all();
    virtual QVector<TEntity> all(Predicate predicate);

    virtual TEntity * find(int id);
    virtual TEntity * find(Predicate predicate);

    virtual void add(const TEntity & item);
    virtual void addAuto(TEntity & item);
    virtual bool contains(const TEntity & item);
    virtual bool contains(Predicate predicate);
    virtual bool update(Predicate predicate, const TEntity & newItem);
    virtual bool update(const TEntity & oldItem, const TEntity & newItem);
    virtual bool remove(Predicate predicate);
    virtual bool remove(const TEntity & item);

    int size() const;

    virtual void save(QDataStream & stream);
    virtual void load(QDataStream & stream);

protected:
    std::list<TEntity> mData;
};

template<class TEntity>
QVector<TEntity> LinkedList<TEntity>::all()
{
    QVector<TEntity> out;

    for(auto it = mData.begin(); it != mData.end(); it++)
        out.push_back(*it);

    return out;
}

template<class TEntity>
QVector<TEntity> LinkedList<TEntity>::all(LinkedList::Predicate predicate)
{
    QVector<TEntity> out;

    for(auto it = mData.begin(); it != mData.end(); it++)
        if(predicate(*it))
            out.push_back(*it);

    return out;
}

template<class TEntity>
TEntity * LinkedList<TEntity>::find(int id)
{
    for(auto & data : mData)
    {
        auto entity = dynamic_cast<TEntity*>(&data);

        if(entity->ID == id)
            return &data;
    }

    return nullptr;
}

template<class TEntity>
TEntity * LinkedList<TEntity>::find(Predicate predicate)
{
    for(auto & data : mData)
        if(predicate(data))
            return &data;

    return nullptr;
}

template<class TEntity>
void LinkedList<TEntity>::add(const TEntity & item)
{
    mData.push_back(item);
}

template<class TEntity>
void LinkedList<TEntity>::addAuto(TEntity & item)
{
    auto entity = dynamic_cast<TEntity*>(&item);

    if(entity != nullptr)
    {
        if(!mData.empty())
        {
            auto last = dynamic_cast<TEntity*>(&mData.back());

            if(last != nullptr)
            {
                entity->ID = last->ID + 1;
            }
        }

        add(item);
    }
}

template<class TEntity>
bool LinkedList<TEntity>::contains(const TEntity &item)
{
    for(auto it = mData.begin(); it != mData.end(); it++)
        if(*it == item)
            return true;

    return false;
}

template<class TEntity>
bool LinkedList<TEntity>::contains(Predicate predicate)
{
    for(auto it = mData.begin(); it != mData.end(); it++)
        if(predicate(*it))
            return true;

    return false;
}

template<class TEntity>
bool LinkedList<TEntity>::update(Predicate predicate, const TEntity &newItem)
{
     for(auto it = mData.begin(); it != mData.end(); it++)
    {
        if(predicate(*it))
        {
            *it = newItem;
            return true;
        }
    }

    return false;
}

template<class TEntity>
bool LinkedList<TEntity>::update(const TEntity &oldItem, const TEntity & newItem)
{
    for(auto it = mData.begin(); it != mData.end(); it++)
    {
        if(*it == oldItem)
        {
            *it = newItem;
            return true;
        }
    }

    return false;
}

template<class TEntity>
bool LinkedList<TEntity>::remove(Predicate predicate)
{
    for(auto it = mData.begin(); it != mData.end(); it++)
    {
        if(predicate(*it))
        {
            mData.erase(it);
            return true;
        }
    }

    return false;
}

template<class TEntity>
bool  LinkedList<TEntity>::remove(const TEntity &item)
{
    for(auto it = mData.begin(); it != mData.end(); it++)
    {
        if(*it == item)
        {
            mData.erase(it);
            return true;
        }
    }

    return false;
}

template<class TEntity>
int LinkedList<TEntity>::size() const
{
    return mData.size();
}

template<class TEntity>
void LinkedList<TEntity>::save(QDataStream & stream)
{
    stream << mData.size();

    for(const auto & data : mData)
        stream << data;
}

template<class TEntity>
void LinkedList<TEntity>::load(QDataStream & stream)
{
    int count;
    TEntity temp;

    stream >> count;

    while(count-- > 0)
    {
        stream >> temp;
        mData.push_back(temp);
    }
}

#endif // LinkedList_HPP
