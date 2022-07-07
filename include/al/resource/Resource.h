#pragma once

#include <sead/prim/seadSafeString.h>

namespace al {

class Resource {
    void* mSeadResource;

public:
    void cleanupResGraphicsFile();
    const char* getArchiveName() const;
    void* getByml(const sead::SafeString&) const;
    const char* getEntryName(sead::BufferedSafeString*, const sead::SafeString&, unsigned int) const;
    void* getFile(const sead::SafeString& name) const;
    size_t getFileSize(const sead::SafeString& name) const;
    void* getKcl(sead::SafeStringBase<char> const&) const;
    void* getOtherFile(sead::SafeStringBase<char> const&) const;
    void* getPa(sead::SafeStringBase<char> const&) const;
    size_t getSize() const;
    bool isExistByml(char const*) const;
    bool isExistFile(sead::SafeStringBase<char> const&) const;
    Resource(sead::SafeStringBase<char> const&);
    void* tryGetByml(sead::SafeStringBase<char> const&) const;
    void* tryGetKcl(sead::SafeStringBase<char> const&) const;
    void* tryGetPa(sead::SafeStringBase<char> const&) const;
};

} // anmespace al