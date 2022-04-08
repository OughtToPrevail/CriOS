#ifndef OSTEST_FUNCTION_H
#define OSTEST_FUNCTION_H

// Learnt how to make this from: https://stackoverflow.com/questions/14936539/how-stdfunction-works

// declare function with basic template
template<class F>
class Function;

// specialize function into a specific function type of Result(Args...), this will break up the template<class F> above into two types, Result and Args (variable args)
template<class Result, class... Args>
class Function<Result(Args...)>
{
public:
	template<class F>  // use <F> here, this will take the lambda type
	Function(F&& func);  // purposefully not explicit (so lambdas can be freely passed to methods)
	// TODO: add destructor

	Result operator()(Args... args) const;  // when this class will be called via the "()" operator it will call the model
private:
	class FunctionConcept  // point of the concept is to have no template, so it can be declared as a field
	{
	public:
		virtual Result operator()(Args... args) const = 0;
	};
	// the model is basically an implementation to strip the <F> type, currently <F> is only available in the constructor, so to use it as a field in the class (_func)
	// would be impossible, which is why we have a concept and model, the concept declares how the model will look without the template and thus can be a field
	// and the model will have the template which will be used to declare the lambda as a field there and then call it
	template<class F>  // again the lambda type
	class FunctionModel : public FunctionConcept
	{
	public:
		template<class F1>  // need to have another template here to now take the reference of F
		explicit FunctionModel(F1&& func);

		Result operator()(Args... args) const override;
	private:
		F _func;  // store lambda as a field
	};

	FunctionConcept* _func;
};

template<class Result, class... Args>
template<class F>
template<class F1>
Function<Result(Args...)>::FunctionModel<F>::FunctionModel(F1&& func) : _func(func)
{

}

template<class Result, class... Args>
template<class F>
Result Function<Result(Args...)>::FunctionModel<F>::operator()(Args... args) const
{
	return this->_func(args...);
}

template<class Result, class... Args>
template<class F>
Function<Result(Args...)>::Function(F&& func) : _func(new FunctionModel<F>(func))
{

}

template<class Result, class... Args>
Result Function<Result(Args...)>::operator()(Args... args) const
{
	return (*this->_func)(args...);
}

#endif //OSTEST_FUNCTION_H