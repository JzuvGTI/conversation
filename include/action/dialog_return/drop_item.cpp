#include "pch.hpp"

#include "drop_item.hpp"

void drop_item(ENetEvent& event, const ::hPipe &hPipe)
{
    ::peer *pPeer = static_cast<::peer*>(event.peer->data);

    auto world = std::ranges::find(worlds, pPeer->recent_worlds.back(), &::world::name);
    if (world == worlds.end()) return;

    const short itemID = atoi(hPipe["itemID"].c_str());
    short count = atoi(hPipe["count"].c_str());
    if (count <= 0) return;

    auto it = std::ranges::find(pPeer->slots, itemID, &::slot::id);
    if (it == pPeer->slots.end() || it->count <= 0) return;

    if (count > it->count) count = it->count;

    modify_item_inventory(event, ::slot(itemID, -count));

    float x_nabor = (pPeer->facing_left) ? pPeer->pos.x - 32 : pPeer->pos.x + 32; // @note peer's naboring tile (drop position)
    add_drop(event, {itemID, count}, {x_nabor, pPeer->pos.y}, *world);
}