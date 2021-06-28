#include "DXUT.h"
#include "cObjectManager.h"

void cObjectManager::Update()
{
	for (int i = 0; i < END; i++)
	{
		for (auto iter = objList[i].begin(); iter != objList[i].end();)
		{
			if (!(*iter)->isDestroy)
			{
				(*iter)->Update();
				iter++;
			}
			else
			{
				for (auto col : COLL->colList)
				{
					if (auto jter = col->colEnterList.find(*iter); jter != col->colEnterList.end())
						col->colEnterList.erase(jter);
				}
				(*iter)->DestroyCollider();
				(*iter)->Release();
				SAFE_DELETE(*iter);
				iter = objList[i].erase(iter);
			}
		}
	}
}

void cObjectManager::Render()
{
	for (int i = 0; i < END; i++)
	{
		for (auto iter = objList[i].begin(); iter != objList[i].end();)
		{
			if (!(*iter)->isDestroy)
			{
				(*iter)->Render();
			}
				iter++;
		}
	}
}

void cObjectManager::Release()
{
	for (int i = 0; i < END; i++)
	{
		for (auto iter = objList[i].begin(); iter != objList[i].end();)
		{
			(*iter)->DestroyCollider();
			(*iter)->Release();
			SAFE_DELETE(*iter);
			iter = objList[i].erase(iter);
		}
		objList[i].clear();
	}
}

cObject* cObjectManager::CreateObj(ObjTag tag, cObject* obj)
{
	cObject* temp = obj;
	temp->tag = tag;
	temp->Init();
	objList[tag].push_back(temp);
	return temp;
}
