#include "pch.hpp"

#include "onVariant/SetClothing.hpp"
#include "onVariant/ConsoleMessage.hpp"

#include "find_item.hpp"

void find_item(ENetEvent& event, const ::hPipe &hPipe)
{
    std::vector<std::string> parts = readch(hPipe["buttonClicked"], '_');
    if (parts.size() < 2) return;

    std::string id = parts[1];
    if (id.empty()) return;

    ::peer *pPeer = static_cast<::peer*>(event.peer->data);
    const short item_id = atoi(id.c_str());
    const ::item &item = id_to_item(item_id);

    if (pPeer->role >= DEVELOPER)
    {
        modify_item_inventory(event, ::slot(item_id, 200));
        on::ConsoleMessage(event.peer, std::format("`2Added 200x `w{}`` to your inventory.", item.raw_name));
    }
    else
    {
        on::ConsoleMessage(event.peer, std::format("`oItem: `w{}`` (ID: `2{}``, Rarity: `2{}``)", item.raw_name, item.id, item.rarity));
    }
}