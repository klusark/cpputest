/*
 * Copyright (c) 2007, Michael Feathers, James Grenning and Bas Vodde
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE EARLIER MENTIONED AUTHORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockNamedValue.h"

TEST_GROUP(ComparatorsAndCopiersRepository)
{
};

class MyComparator : public MockNamedValueComparator
{
  public:

    MyComparator() {}
    virtual ~MyComparator() {}

    virtual bool isEqual(const void*, const void*) { return false; } _override
    virtual SimpleString valueToString(const void*) { return ""; } _override
};

class MyCopier : public MockNamedValueCopier
{
  public:

    MyCopier() {}
    virtual ~MyCopier() {} _override

    virtual void copy(void*, const void*) {} _override
};

TEST(ComparatorsAndCopiersRepository, InstallCopierAndRetrieveIt)
{
  MyCopier copier;
  MockNamedValueComparatorsAndCopiersRepository repository;
  repository.installCopier("MyType", copier);
  POINTERS_EQUAL(&copier, repository.getCopierForType("MyType"));
  repository.clear();
}

TEST(ComparatorsAndCopiersRepository, ComparatorAndCopierByTheSameNameShouldBothBeFound)
{
  MyComparator comparator;
  MyCopier copier;
  MockNamedValueComparatorsAndCopiersRepository repository;
  repository.installCopier("MyType", copier);
  repository.installComparator("MyType", comparator);
  POINTERS_EQUAL(&comparator, repository.getComparatorForType("MyType"));
  POINTERS_EQUAL(&copier, repository.getCopierForType("MyType"));
  repository.clear();
}

