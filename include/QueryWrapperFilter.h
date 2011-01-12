/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef QUERYWRAPPERFILTER_H
#define QUERYWRAPPERFILTER_H

#include "Filter.h"
#include "DocIdSet.h"

namespace Lucene
{
    /// Constrains search results to only match those which also match a provided query.  
    ///
    /// This could be used, for example, with a {@link TermRangeQuery} on a suitably formatted date field to 
    /// implement date filtering.  One could re-use a single QueryFilter that matches, eg., only documents 
    /// modified within the last week.  The QueryFilter and TermRangeQuery would only need to be reconstructed
    /// once per day.
    class LPPAPI QueryWrapperFilter : public Filter
    {
    public:
        /// Constructs a filter which only matches documents matching query.
        QueryWrapperFilter(QueryPtr query);
        
        virtual ~QueryWrapperFilter();
    
        LUCENE_CLASS(QueryWrapperFilter);
    
    protected:
        QueryPtr query;
    
    public:
        virtual DocIdSetPtr getDocIdSet(IndexReaderPtr reader);
        virtual String toString();
        virtual bool equals(LuceneObjectPtr other);
        virtual int32_t hashCode();
    };
    
    class LPPAPI QueryWrapperFilterDocIdSet : public DocIdSet
    {
    public:
        QueryWrapperFilterDocIdSet(IndexReaderPtr reader, WeightPtr weight);
        virtual ~QueryWrapperFilterDocIdSet();
    
        LUCENE_CLASS(QueryWrapperFilterDocIdSet);
    
    protected:
        IndexReaderPtr reader;
        WeightPtr weight;
    
    public:
        virtual DocIdSetIteratorPtr iterator();
        virtual bool isCacheable();
    };
}

#endif
