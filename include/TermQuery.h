/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef TERMQUERY_H
#define TERMQUERY_H

#include "Query.h"
#include "Weight.h"

namespace Lucene
{
    /// A Query that matches documents containing a term.  This may be combined with other terms with a 
    /// {@link BooleanQuery}.
    class LPPAPI TermQuery : public Query
    {
    public:
        /// Constructs a query for the term.
        TermQuery(TermPtr term);
        
        virtual ~TermQuery();
    
        LUCENE_CLASS(TermQuery);
    
    protected:
        TermPtr term;
    
    public:
        using Query::toString;
        
        /// Returns the term of this query.
        TermPtr getTerm();
        
        virtual WeightPtr createWeight(SearcherPtr searcher);
        virtual void extractTerms(SetTerm terms);
        
        /// Prints a user-readable version of this query.
        virtual String toString(const String& field);
        
        virtual bool equals(LuceneObjectPtr other);
        virtual int32_t hashCode();
        virtual LuceneObjectPtr clone(LuceneObjectPtr other = LuceneObjectPtr());
        
        friend class TermWeight;
    };
    
    class LPPAPI TermWeight : public Weight
    {
    public:
        TermWeight(TermQueryPtr query, SearcherPtr searcher);
        virtual ~TermWeight();
    
        LUCENE_CLASS(TermWeight);
    
    protected:
        TermQueryPtr query;
        SimilarityPtr similarity;
        double value;
        double idf;
        double queryNorm;
        double queryWeight;
        IDFExplanationPtr idfExp;
    
    public:
        virtual String toString();
        virtual QueryPtr getQuery();
        virtual double getValue();
        virtual double sumOfSquaredWeights();
        virtual void normalize(double norm);
        virtual ScorerPtr scorer(IndexReaderPtr reader, bool scoreDocsInOrder, bool topScorer);
        virtual ExplanationPtr explain(IndexReaderPtr reader, int32_t doc);
    };
}

#endif
