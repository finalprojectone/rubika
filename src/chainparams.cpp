// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The LightPayCoin developers
// Copyright (c) 2018 The Rubika developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

	//   What makes a good checkpoint block?
	// + Is surrounded by blocks with reasonable timestamps
	//   (no blocks before with a timestamp after, none after with
	//    timestamp before)
	// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("000005fe121efc04f97ed146e1f9049ecdb0dd55b34485d0c881abb70815108e"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1537869600, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1537869601,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1537869602,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x5a;
        pchMessageStart[1] = 0x2b;
        pchMessageStart[2] = 0x3f;
        pchMessageStart[3] = 0x4d;
        vAlertPubKey = ParseHex("043ada803c9b624325bd50bf93b6bc9dfe87e23363ccf21c595bde8615e06e343452a9185a86fa8df3175e39b4f296c0ab94db7ab5c35cdd08cc5e665218177e6a");
        nDefaultPort = 36547;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Rubika starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 1 * 60; // Rubika: 1 day
        nTargetSpacing = 1 * 60;  // Rubika: 1 minute
        nLastPOWBlock = 300;
        nMaturity = 50;
        nMasternodeCountDrift = 20;
        nMasternodeCollateralLimit = 5000;
        nModifierUpdateBlock = 615800;
        nMaxMoneyOut = 60000000 * COIN;

        /**
         algorithm: quark-hash
		merkle hash: 9bf021262f859f2b4fb9f5a07af5ca17c70856b89c00b6502f0b768445be3ec0
		pszTimestamp: The World Cup for the assembly of the Rubik's Cube was visited by the creator of the puzzle
		pubkey: 048ce0222e38cb1a4333baf8014631b5213cb3d53baf7728ae718bda8c4bea81a10a8a50b96815d67b44aebe9691a82a809fb59ed2ba65cc1dbb6202f29077dee6
		time: 1537869601
		bits: 0x1e0ffff0
		genesis hash found!
		nonce: 3824
		genesis hash: 000000065dde9eb02dc613d7c429067c6822d08808c6ec37c2acbed44c589fdf
         */
        const char* pszTimestamp = "The World Cup for the assembly of the Rubik's Cube was visited by the creator of the puzzle";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("048ce0222e38cb1a4333baf8014631b5213cb3d53baf7728ae718bda8c4bea81a10a8a50b96815d67b44aebe9691a82a809fb59ed2ba65cc1dbb6202f29077dee6") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1537869600;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 667420;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("000005fe121efc04f97ed146e1f9049ecdb0dd55b34485d0c881abb70815108e"));
        assert(genesis.hashMerkleRoot == uint256("9bf021262f859f2b4fb9f5a07af5ca17c70856b89c00b6502f0b768445be3ec0"));

		// DNS Seeding
        vSeeds.push_back(CDNSSeedData("seed1.rubikaco.in", "seed1.rubikaco.in"));
        vSeeds.push_back(CDNSSeedData("seed2.rubikaco.in", "seed2.rubikaco.in"));
        vSeeds.push_back(CDNSSeedData("seed3.rubikaco.in", "seed3.rubikaco.in"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 60);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 125);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;		// default true
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;		// default false
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04b745e8b01472b0af59d65d5d3b50f30551eef9c0035481c24b09c83fe9b1ac5a9cd968fe48d64c5e5af7dd244c75532ceec7983a73786af116207b12a8788e3a";
        strObfuscationPoolDummyAddress = "RE2edb4DZEkuVR4oNwKBmW5R6GB9a49cYZ";
        nStartMasternodePayments = 1537869600; //Wed, 25 Jun 2014 20:36:16 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x5b;
        pchMessageStart[1] = 0x2c;
        pchMessageStart[2] = 0x3f;
        pchMessageStart[3] = 0x4d;
        vAlertPubKey = ParseHex("0404cef04f6ed3c159cfb8490875229eff6b48c96b9a8da0aeffa37f800cac12448628ca33650d2d250e98fe433d5f097d1ee1bcbeae82ef38afef94008a0286e4");
        nDefaultPort = 37547;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 1;
        nTargetTimespan = 1 * 60; // Rubika: 1 day
        nTargetSpacing = 1 * 60;  // Rubika: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 20;
        nMasternodeCountDrift = 5;
        nMasternodeCollateralLimit = 5000;
        nModifierUpdateBlock = 100000; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 60000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1537869601;
        genesis.nNonce = 3824;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("000000065dde9eb02dc613d7c429067c6822d08808c6ec37c2acbed44c589fdf"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 136); // Testnet rubika addresses start with 'w' or 'x'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet rubika script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet rubika BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet rubika BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet rubika BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04b9517dc97bdb3c4c8cee77d5a59ae46a015e0f669a8b92cce087ac91abaafdca3c93670617b0053c8dadd5bc868377f1b76532f358e08dab953e1196cbaef680";
        strObfuscationPoolDummyAddress = "RE2edb4DZEkuVR4oNwKBmW5R6GB9a49cYZ";
        nStartMasternodePayments = 1537869601; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x2d;
        pchMessageStart[1] = 0x53;
        pchMessageStart[2] = 0x6f;
        pchMessageStart[3] = 0x40;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Rubika: 1 day
        nTargetSpacing = 1 * 60;        // Rubika: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1537869602;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 430987;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 38547;
        assert(hashGenesisBlock == uint256("000000a238376d5e2497b911d693fe13f67d12ab3681bb5309438c714b2557f5"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 39547;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
