#include "pch.hpp"

#include "onVariant/ConsoleMessage.hpp"

#include "trash_item.hpp"

void trash_item(ENetEvent& event, const ::hPipe &hPipe)
{
    ::peer *pPeer = static_cast<::peer*>(event.peer->data);

    const short itemID = atoi(hPipe["itemID"].c_str());
    short count = atoi(hPipe["count"].c_str());
    if (count <= 0) return;

    const ::item &item = id_to_item(itemID);

    auto it = std::ranges::find(pPeer->slots, itemID, &::slot::id);
    if (it == pPeer->slots.end() || it->count <= 0) return;

    if (count > it->count) count = it->count;

    modify_item_inventory(event, ::slot(itemID, -count));
    on::ConsoleMessage(event.peer, std::format("{} `w{}`` recycled, `w0`` gems earned.", count, item.raw_name));
}