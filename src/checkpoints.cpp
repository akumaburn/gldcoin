// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 GLDcoin Developers

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (     0, uint256("0xdced3542896ed537cb06f9cb064319adb0da615f64dd8c5e5bad974398f44b24"))
			(     1, uint256("0xe39be079a4e57af79f63edb2726bdcb401ae520fa5b5328bbeab185b5b3d636e"))
			(     6048, uint256("0xe8eb14ac03f25fd52a46b51acba8af543f6b4baf1b85b62d6e6e09ba5f108ed7"))
			(     12096, uint256("0xd2bd87d677cced55584634d6d03434e041d5dbbaf5639c873a5f6a654d788ad1"))
			(     16128, uint256("0x290d05c1f5fb2cc75d5bc7657141e4e42d4ee7b4e78a73c96fac878a58d52057"))
			(     18143, uint256("0x996caca04cce6ffc7f1053abcd350742e2ecc3220663cfd3e3585e3442d7cf74"))
			(     18144, uint256("0xed5124e191b92d5405374dc4018203a7e03f4251293b6d5f57a83d1e1ff4df30"))
			(     20160, uint256("0xe19b119f4a633d89320d502e7c05b88d083acdff3b4bd40efcdca54b25f6cb2c"))
			(     20500, uint256("0x23ab64ad71d7191c28010c7c1b0b35d32ac97ace893dbb20068a6abb617f80a4"))
            ;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
