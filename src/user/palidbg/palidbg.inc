// Copyright 2022 MoMA Lab, NYU Abu Dhabi (wp.nyu.edu/momalab/)
#include <typeinfo>

#include "chron.h"

using namespace lbcrypto;

using Element = DCRTPoly;

inline void dpoint(string m)
{
    std::cout << "[" << m << "]\n" << std::flush;
    return;
}

Ciphertext<Element> xc_EvalMult(ConstCiphertext<Element> ciphertext1,
                                ConstCiphertext<Element> ciphertext2,
                                LPAlgorithmSHEBFVrns<Element> & alg,
                                int ver)
{
    dpoint("dpoint0");

    using ParmType = typename Element::Params;


    ///return alg.EvalMult(ciphertext1, ciphertext2);
    Ciphertext<DCRTPoly> newCiphertext = ciphertext1->CloneEmpty();


    const auto cryptoParamsBFVrns =
        std::static_pointer_cast<LPCryptoParametersBFVrns<DCRTPoly>>(
            ciphertext1->GetCryptoContext()->GetCryptoParameters());

    std::vector<DCRTPoly> cipherText1Elements = ciphertext1->GetElements();
    std::vector<DCRTPoly> cipherText2Elements = ciphertext2->GetElements();

    size_t cipherText1ElementsSize = cipherText1Elements.size();
    size_t cipherText2ElementsSize = cipherText2Elements.size();
    size_t cipherTextRElementsSize =
        cipherText1ElementsSize + cipherText2ElementsSize - 1;


    cout << "AAA " << cipherText1ElementsSize << cipherText2ElementsSize
         << cipherTextRElementsSize << ' ' << cipherText1Elements[0].GetLength() << '\n';

    std::vector<DCRTPoly> c(cipherTextRElementsSize);

    const shared_ptr<ParmType> elementParams = cryptoParamsBFVrns->GetElementParams();
    const shared_ptr<ILDCRTParams<BigInteger>> paramsP = cryptoParamsBFVrns->GetParamsP();
    const shared_ptr<ILDCRTParams<BigInteger>> paramsQP = cryptoParamsBFVrns->GetParamsQP();

    // Expands the CRT basis to Q*S; Outputs the polynomials in Format::EVALUATION
    // representation

    dpoint("dpoint1 - start expand");

    for (size_t i = 0; i < cipherText1ElementsSize; i++)
    {
        cipherText1Elements[i].ExpandCRTBasis(
            paramsQP, paramsP, cryptoParamsBFVrns->GetQHatInvModq(),
            cryptoParamsBFVrns->GetQHatInvModqPrecon(),
            cryptoParamsBFVrns->GetQHatModp(), cryptoParamsBFVrns->GetalphaQModp(),
            cryptoParamsBFVrns->GetModpBarrettMu(), cryptoParamsBFVrns->GetqInv());
        ///throw "halt";
    }

    dpoint("dpoint2");

    for (size_t i = 0; i < cipherText2ElementsSize; i++)
    {
        cipherText2Elements[i].ExpandCRTBasis(
            paramsQP, paramsP, cryptoParamsBFVrns->GetQHatInvModq(),
            cryptoParamsBFVrns->GetQHatInvModqPrecon(),
            cryptoParamsBFVrns->GetQHatModp(), cryptoParamsBFVrns->GetalphaQModp(),
            cryptoParamsBFVrns->GetModpBarrettMu(), cryptoParamsBFVrns->GetqInv());
    }



    dpoint("dpoint3 - start point product");

    {
        auto p3b = chron::now();

        const int loop = 10000;
        for ( int i = 0; i < loop; i++ )
        {
            bool * isFirstAdd = new bool[cipherTextRElementsSize];
            std::fill_n(isFirstAdd, cipherTextRElementsSize, true);

            for (size_t i = 0; i < cipherText1ElementsSize; i++)
            {
                for (size_t j = 0; j < cipherText2ElementsSize; j++)
                {
                    if (isFirstAdd[i + j] == true)
                    {
                        c[i + j] = cipherText1Elements[i] * cipherText2Elements[j];
                        isFirstAdd[i + j] = false;
                    }
                    else
                    {
                        c[i + j] += cipherText1Elements[i] * cipherText2Elements[j];
                    }
                }
            }

            delete[] isFirstAdd;
        }

        auto p3e = chron::now();
        cout << "3 took : " << (p3e-p3b) << "ms x" << loop << "\n";
    }

    {

        const int loop = 10000;
		auto c0 = c[0];
		///volatile 
		decltype(c0) cc[loop];
        ///for ( int i = 0; i < loop; i++ ) cc.push_back(c[0]);
        for ( int i = 0; i < loop; i++ ) cc[i] = c[0];

        auto p3b = chron::now();

        for ( int i = 0; i < loop; i++ )
        {
	        cc[i].SwitchFormat();
        }

        auto p3e = chron::now();
        cout << "Switch format took : " << (p3e-p3b) << "ms x" << loop << "\n";
    }


    dpoint("dpoint4 - start conversion back");

    for (size_t i = 0; i < cipherTextRElementsSize; i++)
    {
        // converts to coefficient representation before rounding
        c[i].SwitchFormat();
        // Performs the scaling by t/Q followed by rounding; the result is in the
        // CRT basis P
        c[i] = c[i].ScaleAndRound(paramsP,
                                  cryptoParamsBFVrns->GettPSHatInvModsDivsModp(),
                                  cryptoParamsBFVrns->GettPSHatInvModsDivsFrac(),
                                  cryptoParamsBFVrns->GetModpBarrettMu());

        // Converts from the CRT basis P to Q
        c[i] = c[i].SwitchCRTBasis(
                   elementParams, cryptoParamsBFVrns->GetPHatInvModp(),
                   cryptoParamsBFVrns->GetPHatInvModpPrecon(),
                   cryptoParamsBFVrns->GetPHatModq(), cryptoParamsBFVrns->GetalphaPModq(),
                   cryptoParamsBFVrns->GetModqBarrettMu(), cryptoParamsBFVrns->GetpInv());
    }

    dpoint("dpoint5 - finished");


    newCiphertext->SetElements(std::move(c));
    newCiphertext->SetDepth((ciphertext1->GetDepth() + ciphertext2->GetDepth()));

    dpoint("dpoint6");
    return newCiphertext;
}

Ciphertext<Element> xb_EvalMult(ConstCiphertext<Element> ct1,
                                ConstCiphertext<Element> ct2,
                                LPAlgorithmSHEBFVrns<Element> & alg,
                                int ver)
{

    if ( ver > 1 )
    {
        auto rv = xc_EvalMult(ct1, ct2, alg, ver);
        return rv;
    }

    if ( ver == 1 )
    {
        auto rv = alg.EvalMult(ct1, ct2);
        return rv;
    }

    throw "Bad ver " + std::to_string(ver);
}

Ciphertext<Element> xa_EvalMult(ConstCiphertext<Element> ct1,
                                ConstCiphertext<Element> ct2,
                                e3::pali::Cc & cc, int ver)
{
    LPEvalKey<Element> ek = cc->GetEvalMultKeyVector(ct1->GetKeyTag())[0];

    const shared_ptr<LPPublicKeyEncryptionScheme<Element>> alg1 = cc->GetEncryptionAlgorithm();

    LPPublicKeyEncryptionSchemeBFVrns<Element> * p =
        dynamic_cast<LPPublicKeyEncryptionSchemeBFVrns<Element>*>(alg1.get());

    if ( !p ) throw "not LPPublicKeyEncryptionSchemeBFVrns";

    std::shared_ptr<LPSHEAlgorithm<Element>> alg2 = p->m_algorithmSHE;
    LPSHEAlgorithm<Element> * palg2 = alg2.get();


    auto * q = dynamic_cast<LPAlgorithmSHEBFVrns<Element>*>(palg2);
    if ( !q ) throw "not LPAlgorithmSHEBGVrns";

    //auto rv1 = q->EvalMult(ct1, ct2);
    auto rv1 = xb_EvalMult(ct1, ct2, *q, ver);

    if (1)
    {
        auto rv2 = q->KeySwitch(ek, rv1);
        return rv2;
    }
    else
    {
        cout << "KeySwitch OFF\t";
        return rv1;
    }
}

e3::PaliBfvNativeCiphertext x_op_mul
(const e3::PaliBfvNativeCiphertext & x, const e3::PaliBfvNativeCiphertext & a,
 void * pcc, int ver)
{
    e3::PaliBfvNativeCiphertext r;
    e3::pali::Cc & cc = *e3::pali::tocc(pcc);

    //auto ctadd = cc->EvalMult(x.p->ct, a.p->ct);
    auto ctadd = xa_EvalMult(x.p->ct, a.p->ct, cc, ver);
    //**

    r.p = std::shared_ptr<e3::PaliBfvCiphertext>(new e3::PaliBfvCiphertext {ctadd});
    return r;
}


e3::PaliBfvNativeCiphertext opmul(e3::PaliBfvNativeCiphertext & x,
                                  e3::PaliBfvNativeCiphertext & y,
                                  e3::PaliBfvNativePrivKey & cc,
                                  int ver)
{
    if ( ver > 0 )
    {
        auto z = x_op_mul(x, y, cc, ver);
        return z;
    }

    auto z = x.op_mul(y, cc);
    return z;
}

