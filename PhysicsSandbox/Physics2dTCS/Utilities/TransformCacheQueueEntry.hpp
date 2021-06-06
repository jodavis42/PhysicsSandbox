#pragma once

#include "Physics2dStandardTCS.hpp"

namespace Physics2dTCS
{

//-------------------------------------------------------------------TransformCacheQueueEntry
class TransformCacheQueueEntry
{
public:
  bool mQueued = false;
  Link<TransformCacheQueueEntry> mLink;
};

}//namespace Physics2dTCS
