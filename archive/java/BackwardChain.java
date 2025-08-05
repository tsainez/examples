//
// BackwardChain
//
// This class implements a backward chaining inference procedure. The
// implementation is very skeletal, and the resulting reasoning process is
// not particularly efficient. Knowledge is restricted to the form of
// definite clauses, grouped into a list of positive literals (facts) and
// a list of Horn clause implications (rules). The inference procedure
// maintains a list of goals. On each step, a proof is sought for the
// first goal in this list, starting by an attempt to unify the goal with
// any known fact in the knowledge base. If this fails, the rules are
// examined in the order in which they appear in the knowledge base, searching
// for a consequent that unifies with the goal. Upon successful unification,
// a proof is sought for the conjunction of the rule antecedents. If this
// fails, further rules are considered. Note that this is a strictly
// depth-first approach, so it is incomplete. Note, also, that there is
// no backtracking with regard to matches to facts -- the first match is
// always taken and other potential matches are ignored. This can make
// the algorithm incomplete in another way. In short, the order in which
// facts and rules appear in the knowledge base can have a large influence
// on the behavior of this inference procedure.
//
// In order to use this inference engine, the knowledge base must be
// initialized by a call to "initKB". Queries are then submitted using the
// "ask" method. The "ask" function returns a binding list which includes
// bindings for intermediate variables.
//
// David Noelle -- Tue Oct  9 18:48:57 PDT 2018
//                 Modified Mon Oct 12 17:18:55 PDT 2020

//
// Modified 11/6/2020 by Anthony Sainez
// Resources used:
//		* 	https://docs.oracle.com/javase/7/docs/api/java/util/Set.html
//		* 	https://docs.oracle.com/javase/tutorial/java/nutsandbolts/op2.html
//		* 	http://www.cs.trincoll.edu/~ram/cpsc352/notes/unification.html
// 		* 	https://www-users.cs.umn.edu/~gini/4511/unification.html
//		* 	Xeuqing Deng provided psuedocode that I converted into Java.
//		* 	I sought help from classmates in the ACM discord, where we didn't share code but talked about the
//			rough logicof each function.
//

import javax.swing.*;
import java.util.*;


public class BackwardChain {

    public KnowledgeBase kb;

	// Default constructor ...
	public BackwardChain() {
		this.kb = new KnowledgeBase();
	}

	// initKB -- Initialize the knowledge base by interactively requesting
	// file names and reading those files. Return false on error.
	public boolean initKB() {
		return (kb.readKB());
	}

	// START STUDENT SOLUTION CODE SECTION
	// Do not modify this comment or anything above it, with the
	// exception of the file header comment.

	// unifyCC -- Return the most general unifier for the two provided
	// constants, or null if no unification is possible. The argument
	// binding list may be assumed to have been freshly allocated.
	BindingList unifyCC(Term t1, Term t2, BindingList bl) {

	    // PLACE STUDENT SOLUTION CODE HERE
		return t1.equals(t2) ? bl : null;

		// The above code has the same structure as a basic if-else statement, but it can be
		// simplified into a one-liner using the ternary operator. See https://docs.oracle.com/javase/tutorial/java/nutsandbolts/op2.html
		// I also used this online resource: http://www.cs.trincoll.edu/~ram/cpsc352/notes/unification.html
	}
	
	// unifyCV -- Return the most general unifier for the two provided
	// terms, a constant and a variable, or null if no unification is
	// possible. The argument binding list may be assumed to have been
	// freshly allocated.
	BindingList unifyCV(Term t1, Term t2, BindingList bl) {

	    // PLACE STUDENT SOLUTION CODE HERE
		// We can switch the order of the terms and just use our original function.
		// I used this resource. https://www-users.cs.umn.edu/~gini/4511/unification.html
		return unifyVC(t2, t1, bl);
	}
	
	// unifyCF -- Return the most general unifier for the two provided
	// terms, a constant and a function, or null if no unification is
	// possible. The argument binding list may be assumed to have been
	// freshly allocated.
	BindingList unifyCF(Term t1, Term t2, BindingList bl) {

	    // PLACE STUDENT SOLUTION CODE HERE
		// A constant and a function can never be unified.
		// This was revealed in the practice quiz for this assignment.
		return null;
	}

	// unifyVC -- Return the most general unifier for the two provided
	// terms, a variable and a constant, or null if no unification is
	// possible. The argument binding list may be assumed to have been
	// freshly allocated.
	BindingList unifyVC(Term t1, Term t2, BindingList bl) {

	    // PLACE STUDENT SOLUTION CODE HERE
		// Look for any bound values associated with t1.
		Term values = bl.boundValue(t1.v);
		if (values != null) {
			// If a variable is found, attempt to unify by returning a unify call with t1 and bound value.
			return unify(t2, values, bl);
		} else {
			// Otherwise, you can just bind the parameters together and add them to the binding list.
			bl.addBinding(t1.v, t2);
			return bl;
		}
	}
	
	// unifyVV -- Return the most general unifier for the two provided
	// variables, or null if no unification is possible. The argument
	// binding list may be assumed to have been freshly allocated.
	BindingList unifyVV(Term t1, Term t2, BindingList bl) {

	    // PLACE STUDENT SOLUTION CODE HERE
		// It first checks and saves any bound values in the binding list for both variables.
		// Then if there are values found for both variables, it returns an attempt to unify with both values substituted
		// for the variables. otherwise both variables can simply be bound and added to the binding list.
		// Credit to Xeuqing Deng for providing some psuedocode to help me get started.
		if(t1.equals(t2)) {
			return bl;
		} else {
			Term value1 = bl.boundValue(t1.v);
			if (value1 != null) {
				// Turn this into a problem we can handle with other functions
				return unify(value1, t2, bl);
			} else {
				Term value2 = bl.boundValue(t2.v);
				if (value2 != null) {
					// Turn this into a problem we can handle with other functions
					return unify(value2, t1, bl);
				} else {
					bl.addBinding(value2.v, t1);
				}
			}
		}
		return bl;
	}
	
	// unifyVF -- Return the most general unifier for the two provided
	// terms, a variable and a function, or null if no unification is
	// possible. The argument binding list may be assumed to have been
	// freshly allocated.
	BindingList unifyVF(Term t1, Term t2, BindingList bl) {

	    // PLACE STUDENT SOLUTION CODE HERE
		if (t1.allVariables().contains(t2.v)) {
			// First checked if the given variable is an argument of the function provided.
			return null;
		} else {
			// If the variable was not in the function, then the variable and the function can be bound
			// and added to the binding list
			bl.addBinding(t1.v, t2);
			return bl;
		}
	}
	
	// unifyFC -- Return the most general unifier for the two provided
	// terms, a function and a constant, or null if no unification is
	// possible. The argument binding list may be assumed to have been
	// freshly allocated.
	BindingList unifyFC(Term t1, Term t2, BindingList bl) {

	    // PLACE STUDENT SOLUTION CODE HERE
		// A constant and a function can never be unified.
		// This was revealed in the practice quiz for this assignment.
		return null;
	}
	
	// unifyFV -- Return the most general unifier for the two provided
	// terms, a function and a variable, or null if no unification is
	// possible. The argument binding list may be assumed to have been
	// freshly allocated.
	BindingList unifyFV(Term t1, Term t2, BindingList bl) {

		// PLACE STUDENT SOLUTION CODE HERE
		// This is a reversed version of unifyVF, so we will call that function instead.
		return unifyVF(t2, t1, bl);
	}
	
	// unifyFF -- Return the most general unifier for the two provided
	// terms, both functions, or null if no unification is possible.
	// The argument binding list may be assumed to have been freshly
	// allocated.
	BindingList unifyFF(Term t1, Term t2, BindingList bl) {

	    // PLACE STUDENT SOLUTION CODE HERE
		return (unify(t1.f, t2.f, bl)); // This will recursively reduce the abstraction of this.
	}

	// END STUDENT SOLUTION CODE SECTION
	// Do not modify this comment or anything below it.
	
	// unify -- Return the most general unifier for the two provided terms,
	// or null if no unification is possible. The returned binding list
	// should be freshly allocated.
	public BindingList unify(Term t1, Term t2, BindingList bl) {
		BindingList newBL = new BindingList(bl);
		if (t1.isConstant()) {
			if (t2.isConstant()) {
				return (unifyCC(t1, t2, newBL));
			}
			if (t2.isVariable()) {
				return (unifyCV(t1, t2, newBL));
			}
			if (t2.isFunction()) {
				return (unifyCF(t1, t2, newBL));
			}
		}
		if (t1.isVariable()) {
			if (t2.isConstant()) {
				return (unifyVC(t1, t2, newBL));
			}
			if (t2.isVariable()) {
				return (unifyVV(t1, t2, newBL));
			}
			if (t2.isFunction()) {
				return (unifyVF(t1, t2, newBL));
			}
		}
		if (t1.isFunction()) {
			if (t2.isConstant()) {
				return (unifyFC(t1, t2, newBL));
			}
			if (t2.isVariable()) {
				return (unifyFV(t1, t2, newBL));
			}
			if (t2.isFunction()) {
				return (unifyFF(t1, t2, newBL));
			}
		}
		// We should never get here, but ...
		return (null);
	}

	// unify -- Return the most general unifier for the two provided literals,
	// or null if no unification is possible. The returned binding list
	// should be freshly allocated.
	public BindingList unify(Literal lit1, Literal lit2, BindingList bl) {
		if (!(lit1.pred.equals(lit2.pred))) {
			// Different predicates, so no match ...
			return (null);
		}
		// The literals match if the arguments match ...
		return (unify(lit1.args, lit2.args, bl));
	}
		
	// unify -- Return the most general unifier for the two provided lists of
	// terms, or null if no unification is possible. The returned binding list
	// should be freshly allocated.
	public BindingList unify(Function f1, Function f2, BindingList bl) {
		if (!(f1.func.equals(f2.func))) {
			// Different function names, so no match ...
			return (null);
		}
		// The terms match if the arguments match ...
		return (unify(f1.args, f2.args, bl));
	}

	// unify -- Return the most general unifier for the two provided lists of
	// terms, or null if no unification is possible. The returned binding
	// list should be freshly allocated.
	public BindingList unify(List<Term> ts1, List<Term> ts2, BindingList bl) {
		if (bl == null)
			return (null);
		if ((ts1.size() == 0) && (ts2.size() == 0))
			// Empty lists match other empty lists ...
			return (new BindingList(bl));
		if ((ts1.size() == 0) || (ts2.size() == 0))
			// Ran out of arguments in one list before reaching the
			// end of the other list, which means the two argument lists
			// can't match ...
			return (null);
		List<Term> terms1 = new LinkedList<Term>();
		List<Term> terms2 = new LinkedList<Term>();
		terms1.addAll(ts1);
		terms2.addAll(ts2);
		Term t1 = terms1.get(0);
		Term t2 = terms2.get(0);
		terms1.remove(0);
		terms2.remove(0);
		return (unify(terms1, terms2, unify(t1, t2, bl)));
	}

	// askFacts -- Examine all of the facts in the knowledge base to
	// determine if any of them unify with the given literal, under the
	// given binding list. If a unification is found, return the
	// corresponding most general unifier. If none is found, return null
	// to indicate failure.
	BindingList askFacts(Literal lit, BindingList bl) {
		BindingList mgu = null; // Most General Unifier
		for (Literal fact : kb.facts) {
			mgu = unify(lit, fact, bl);
			if (mgu != null)
				return (mgu);
		}
		return (null);
	}

	// askFacts -- Examine all of the facts in the knowledge base to
	// determine if any of them unify with the given literal. If a
	// unification is found, return the corresponding most general unifier.
	// If none is found, return null to indicate failure.
	BindingList askFacts(Literal lit) {
		return (askFacts(lit, new BindingList()));
	}

	// ask -- Try to prove the given goal literal, under the constraints of
	// the given binding list, using both the list of known facts and the
	// collection of known rules. Terminate as soon as a proof is found,
	// returning the resulting binding list for that proof. Return null if
	// no proof can be found. The returned binding list should be freshly
	// allocated.
	BindingList ask(Literal goal, BindingList bl) {
		BindingList result = askFacts(goal, bl);
		if (result != null) {
			// The literal can be unified with a known fact ...
			return (result);
		}
		// Need to look at rules ...
		for (Rule candidateRule : kb.rules) {
			if (candidateRule.consequent.pred.equals(goal.pred)) {
				// The rule head uses the same predicate as the goal ...
				// Standardize apart ...
				Rule r = candidateRule.standardizeApart();
				// Check to see if the consequent unifies with the goal ...
				result = unify(goal, r.consequent, bl);
				if (result != null) {
					// This rule might be part of a proof, if we can prove
					// the rule's antecedents ...
					result = ask(r.antecedents, result);
					if (result != null) {
						// The antecedents have been proven, so the goal
						// is proven ...
						return (result);
					}
				}
			}
		}
		// No rule that matches has antecedents that can be proven. Thus,
		// the search fails ...
		return (null);
	}

	// ask -- Try to prove the given goal literal using both the list of
	// known facts and the collection of known rules. Terminate as soon as
	// a proof is found, returning the resulting binding list for that proof.
	// Return null if no proof can be found. The returned binding list
	// should be freshly allocated.
	BindingList ask(Literal goal) {
		return (ask(goal, new BindingList()));
	}

	// ask -- Try to prove the given list of goal literals, under the
	// constraints of the given binding list, using both the list of known
	// facts and the collection of known rules. Terminate as soon as a proof
	// is found, returning the resulting binding list for that proof. Return
	// null if no proof can be found. The returned binding list should be
	// freshly allocated.
	BindingList ask(List<Literal> goals, BindingList bl) {
		if (goals.size() == 0) {
			// All goals have been satisfied ...
			return (bl);
		} else {
			List<Literal> newGoals = new LinkedList<Literal>();
			newGoals.addAll(goals);
			Literal goal = newGoals.get(0);
			newGoals.remove(0);
			BindingList firstBL = ask(goal, bl);
			if (firstBL == null) {
				// Failure to prove one of the goals ...
				return (null);
			} else {
				// Try to prove the remaining goals ...
				return (ask(newGoals, firstBL));
			}
		}
	}

}

