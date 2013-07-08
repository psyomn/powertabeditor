/*
  * Copyright (C) 2013 Cameron White
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCORE_KEYSIGNATURE_H
#define SCORE_KEYSIGNATURE_H

#include <boost/cstdint.hpp>
#include <boost/serialization/access.hpp>
#include <iosfwd>

namespace Score {

class KeySignature
{
public:
    enum KeyType
    {
        Major,
        Minor
    };

    KeySignature();
    KeySignature(KeyType type, uint8_t accidentals, bool usesSharps);

    bool operator==(const KeySignature &other) const;

    /// Returns the key signature type (major or minor).
    KeyType getKeyType() const;
    /// Sets the key signature type (major or minor).
    void setKeyType(KeyType type);

    /// Returns the number of accidentals in the key signature.
    /// @param includeCancel Indicates whether accidentals for a cancellation
    /// key signature should be included.
    uint8_t getNumAccidentals(bool includeCancel = false) const;
    /// Sets the number of accidentals in the key signature.
    void setNumAccidentals(uint8_t accidentals);

    /// Returns whether the key signature uses sharps or flats.
    bool usesSharps() const;
    /// Sets whether the key signature uses sharps or flats.
    void setSharps(bool sharps);

    /// Returns whether the key signature should be displayed.
    bool isVisible() const;
    /// Sets whether the key signature should be displayed.
    void setVisible(bool visible);

    /// Returns whether the key signature is a cancellation.
    bool isCancellation() const;
    /// Sets whether the key signature is a cancellation.
    void setCancellation(bool cancellation);

    /// The maximum valid number of accidentals.
    static const uint8_t MAX_NUM_ACCIDENTALS;

private:
    KeyType myKeyType;
    uint8_t myNumAccidentals;
    bool myUsesSharps;
    bool myIsVisible;
    bool myIsCancellation;

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int /*version*/)
    {
        ar & myKeyType & myNumAccidentals & myUsesSharps & myIsVisible &
             myIsCancellation;
    }
};

std::ostream& operator<<(std::ostream &os, const KeySignature &key);

}

#endif
