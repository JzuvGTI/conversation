#include "pch.hpp"

#include "onVariant/ConsoleMessage.hpp"
#include "onVariant/SetBux.hpp"

#include "sb.hpp"

void sb(ENetEvent& event, const std::string_view text)
{
    if (text.size() <= sizeof("sb ")-1) return; // @note "/sb" with no message: substr() would throw and crash the server
    const std::string message{ text.substr(sizeof("sb ")-1) };
    ::peer *pPeer = static_cast<::peer*>(event.peer->data);

    if (pPeer->role < MODERATOR)
    {
        constexpr long long sb_cost = 200;
        if (pPeer->gems < sb_cost)
        {
            send_action(event.peer, "log", "msg|`4You need 200 Gems to send a Super Broadcast!");
            return;
        }
        pPeer->gems -= sb_cost;
        pPeer->mysql_update("gems", pPeer->gems);
        on::SetBux(event);
    }

    auto world = std::ranges::find(worlds, pPeer->recent_worlds.back(), &::world::name);
    if (world == worlds.end()) return;

    std::string display = pPeer->recent_worlds.back();
    peers("", PeerSearch::EVERYONE, [&event, &pPeer, message, display](ENetPeer *peer) 
    {
        on::ConsoleMessage(peer, 
            std::format(
                "CP:0_PL:0_OID:_CT:[SB]_ `5** from ({}```5) in [```${}```5] ** : ```${}``",
                pPeer->display_growid, display, message
            )
        );
    });
}