// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2017.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Hannes Roest $
// $Authors: Hannes Roest $
// --------------------------------------------------------------------------

#ifndef OPENMS_ANALYSIS_OPENSWATH_DATAACCESS_SPECTRUMACCESSOPENMSINMEMORY_H
#define OPENMS_ANALYSIS_OPENSWATH_DATAACCESS_SPECTRUMACCESSOPENMSINMEMORY_H

#include <OpenMS/KERNEL/StandardTypes.h>
#include <OpenMS/KERNEL/MSSpectrum.h>
#include <OpenMS/KERNEL/MSChromatogram.h>
#include <OpenMS/KERNEL/MSExperiment.h>

#include <OpenMS/OPENSWATHALGO/DATAACCESS/ISpectrumAccess.h>

#include <boost/shared_ptr.hpp>
#include <algorithm>    // std::lower_bound, std::upper_bound, std::sort

namespace OpenMS
{
  /**
   * @brief An implementation of the OpenSWATH Spectrum Access interface completely in memory
   * 
   * This implementation of the spectrum access interface ensures that all data
   * is held completely in memory and is quickly accessible. This class can be
   * generated by passing any object implementing the Spectrum Access interface
   * and guarantees to provide the same access to the raw data as the original
   * object with the added benefits (and downside) of keeping all data in system
   * memory.
   * 
   * A possible example
   * 
   * @code
   * OpenSwath::ISpectrumAccess * data_access;
   * fillData(data_access); // assume that data_access points to some data
   * OpenSwath::ISpectrumAccess * in_memory_data_access = SpectrumAccessOpenMSInMemory(data_access);
   * @endcode
   *
   * After executing this code, two variables exist: data_access which provides
   * access to the original data but does so in one of multiple ways which is
   * not transparent to the user. However, in_memory_data_access will provide
   * access to the same data but with the guarantee that the data is available
   * in memory and not read from the disk.
   *
  */
  class OPENMS_DLLAPI SpectrumAccessOpenMSInMemory :
    public OpenSwath::ISpectrumAccess
  {
public:
    typedef OpenMS::PeakMap MSExperimentType;
    typedef OpenMS::MSSpectrum MSSpectrumType;
    typedef OpenMS::MSChromatogram MSChromatogramType;

    /// Constructor
    explicit SpectrumAccessOpenMSInMemory(OpenSwath::ISpectrumAccess & origin);

    /// Destructor
    ~SpectrumAccessOpenMSInMemory() override;

    /// Copy constructor
    SpectrumAccessOpenMSInMemory(const SpectrumAccessOpenMSInMemory & rhs);

    /// Light clone operator (actual data will not get copied)
    boost::shared_ptr<OpenSwath::ISpectrumAccess> lightClone() const override;

    OpenSwath::SpectrumPtr getSpectrumById(int id) override;

    OpenSwath::SpectrumMeta getSpectrumMetaById(int id) const override;

    std::vector<std::size_t> getSpectraByRT(double RT, double deltaRT) const override;

    size_t getNrSpectra() const override;

    OpenSwath::ChromatogramPtr getChromatogramById(int id) override;

    size_t getNrChromatograms() const override;

    std::string getChromatogramNativeID(int id) const override;

private:

    std::vector< OpenSwath::SpectrumPtr > spectra_;
    std::vector< OpenSwath::SpectrumMeta > spectra_meta_;

    std::vector< OpenSwath::ChromatogramPtr > chromatograms_;
    std::vector< std::string > chromatogram_ids_;

  };

} //end namespace OpenMS

#endif // OPENMS_ANALYSIS_OPENSWATH_DATAACCESS_SPECTRUMACCESSOPENMSINMEMORY_H
