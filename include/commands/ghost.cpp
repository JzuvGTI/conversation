#include "pch.hpp"

#include "onVariant/SetClothing.hpp"

#include "ghost.hpp"

void ghost(ENetEvent& event, const std::string_view text)
{
    ::peer *pPeer = static_cast<::peer*>(event.peer->data);
    if (pPeer->role < MODERATOR)
    {
        send_action(event.peer, "log", "msg|`4You need to be a Moderator or Developer to use /ghost.");
        return;
    }

    pPeer->state ^= S_GHOST;

    on::SetClothing(event.peer);
}