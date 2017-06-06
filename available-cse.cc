#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CFG.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <iostream>
#include <unordered_map>
#include <set>
#include<vector>
#include <algorithm> 
namespace
{
	struct BasicBlockInfo
	{
		std::set<std::string> gen;
		std::set<std::string> in;
		std::set<std::string> out;
	};
	std::set<std::string> dummy;
	std::set<std::string> seto;
	std::set<std::string> seti;
	std::set<std::string> setg;
 struct Instruction
 {
	std::set<std::string> inseti;
	std::set<std::string> inseto;
	std::set<std::string> insetg;
 };
	std::vector< std::vector<std::string> > vresult;
	std::vector<std::string> vresult1;
	std::vector<std::string> vresult2;
	
	std::set<std::string> dset;
	
	bool check1;
	bool &check2=check1;
	bool check3;
	bool &check4=check3;
	int i=0,i2=0,ig=0,count=0;
	int n,n1,ng;
	std::string exp="";
	std::string exp1;
	std::string expi;
	std::unordered_map<std::string,BasicBlockInfo*> basic_block_table;
	std::map<std::string,Instruction*> Instruction_table;
	BasicBlockInfo *BBI;
	Instruction* INS;
	bool ExtendSet(std::set<std::string> &set1,std::set<std::string> &set2)
	{
		int last_size=set1.size();
		for(const std::string &s : set2)
			set1.insert(s);
		return set1.size()-last_size;
	}

	void PrintSetg(std::set<std::string> &set)
	{
		llvm::errs()<<"gen="<<"{";
		for(const std::string &s:set)
			llvm::errs()<<' '<<s;
		llvm::errs()<<"}\n";
	}
	void PrintSeto(std::set<std::string> &set)
	{
			llvm::errs()<<"out="<<"{";
			for(const std::string &s:set)
					llvm::errs()<<' '<<s;
			llvm::errs()<<"}\n";
	}
	void PrintSeti(std::set<std::string> &set)
	{
			llvm::errs()<<"in="<<"{";
			for(const std::string &s:set)
					llvm::errs()<<' '<<s;
			llvm::errs()<<"}\n";
	}
class PrintPass : public llvm::FunctionPass
{
	public:
	//Structure

	// Identifier
	static char ID;
	// Constructor. The first argument of the parent constructor is
	// a unique pass identifier.
	PrintPass() : llvm::FunctionPass(ID) { }
	// Virtual function overridden to implement the pass functionality.
	bool runOnFunction(llvm::Function &function) override
	{
		// Print function name
		llvm::errs() << "Analysis Pass on function: " << function.getName() <<"Available Expressions"<< '\n';
		// Traverse basic blocks in function
		for (llvm::Function::iterator basic_block = function.begin(),
		e = function.end();
		basic_block != e;
		++basic_block)
		{
			BBI=new BasicBlockInfo;
			basic_block_table.insert({(*basic_block).getName(),BBI});
			i++;
			for(llvm::BasicBlock::iterator ins=basic_block->begin(),e=basic_block->end();ins!=e;++ins)
			{
				INS=new Instruction;
				Instruction_table.insert({(*ins).getName(),INS});
			}
		}
		n=i;
		i=0;
		//---------Project---------------------//
		for (llvm::Function::iterator basic_block = function.begin(),
		e = function.end();
		basic_block != e;
		++basic_block,i++)
		{
		if(i==(n-1))
		{
			i2=0;
			for(llvm::BasicBlock::iterator ins=basic_block->begin(),e=basic_block->end();ins!=e;++ins)
			{
			i2++;
			}
			n1=i2;
			i2=0;
			for(llvm::BasicBlock::iterator ins=basic_block->begin(),e=basic_block->end();ins!=e;++ins,i2++)
			{
			if(i2<n1-1)
			{
			expi=ins->getName();
			exp=ins->getOpcodeName();
			for (unsigned i1 = 0; i1 < (ins->getNumOperands()); i1++)
			{
				llvm::Value *arg = ins->getOperand(i1);
				exp1=(arg->getName());
				if(exp1=="")
				{
					llvm::ConstantInt* I=llvm::dyn_cast<llvm::ConstantInt>(arg);
					int ss1=I->getSExtValue();
					exp1=std::to_string(ss1);
				}
				exp=exp+ exp1;
			}
			std::string d= ins->getOpcodeName();
			if(d!="store")
			{
			//exp=expi+"="+exp;
			}
			dummy.insert(exp);
			}
			}
			//llvm::errs() << basic_block->getName() << " :";
			((basic_block_table[basic_block->getName()])->out).clear();
		 
			llvm::errs() <<'\n' ;
		}
		else
		{
			i2=0;
			for(llvm::BasicBlock::iterator ins=basic_block->begin(),e=basic_block->end();ins!=e;++ins)
			{
			i2++;
			}
			n1=i2;
			i2=0;
			for(llvm::BasicBlock::iterator ins=basic_block->begin(),e=basic_block->end();ins!=e;++ins,i2++)
			{
				if(i2<n1-1)
				{
				expi=ins->getName();
				exp=ins->getOpcodeName();
				for (unsigned i1 = 0; i1 < (ins->getNumOperands()); i1++)
				{
				llvm::Value *arg = ins->getOperand(i1);
				exp1=(arg->getName());
				if(exp1=="")
				{
					llvm::ConstantInt* I=llvm::dyn_cast<llvm::ConstantInt>(arg);
					int ss=I->getSExtValue();
					exp1=std::to_string(ss);
				}
				exp=exp+ exp1;
				}
				std::string d1= ins->getOpcodeName();
				if(d1!="store")
				{
				//exp=expi+"="+exp;
				}
				dummy.insert(exp);
				//((basic_block_table[basic_block->getName()])->out.insert(exp));
				}
			}
		}
	}
	i=0;
	for (llvm::Function::iterator basic_block = function.begin(),
	e = function.end();
	basic_block != e;
	++basic_block,i++)
	{
		if(i<n-1)
		{
			ExtendSet((basic_block_table[basic_block->getName()])->out,dummy);
		}
		llvm::errs() << basic_block->getName() << ": ";
		PrintSeto((basic_block_table[basic_block->getName()])->out);
		llvm::errs() <<'\n';
	}
	//-----------------------Project--------------------------//
		llvm::errs() << "--------" << '\n';
		do
		{
			check1=0;
			check3=0;
			for (llvm::Function::iterator basic_block = function.begin(),
			e = function.end();
			basic_block != e;
			++basic_block)
			{
				printBasicBlock(*basic_block);
			}
		}while(check2||check4);
		return true;
	}
	void printBasicBlock(llvm::BasicBlock &basic_block)
	{
		llvm::errs() << " Basic block " << basic_block.getName() << '\n';

		llvm::errs() << " Predecessors: {";
		std::set<std::string>::iterator its;
		count=0;
		vresult.clear();
		for (llvm::pred_iterator it = pred_begin(&basic_block),
		e = llvm::pred_end(&basic_block);
		it != e;
		++it)
		{
		llvm::BasicBlock *pred = *it;
		llvm::errs() << ' ' << pred->getName();
		//ExtendSet((basic_block_table[basic_block.getName()])->in,(basic_block_table[pred->getName()])->out);
		//vresult.push_back((basic_block_table[pred->getName()])->out);
		vresult2.clear();
		for(its=((basic_block_table[pred->getName()])->out.begin());its!=(basic_block_table[pred->getName()])->out.end();++its)
		{
			vresult2.push_back(*its);
		}
		vresult.push_back(vresult2);
		count++;
		}
		if(count>=1)
		{
		vresult1=vresult[0];
		//llvm::errs()<<"size"<<vresult.size();
		for(int i=1;i<vresult.size();i++)
		{
			vresult1=instersection(vresult1,vresult[i]);
		}
		std::vector<std::string>::iterator itv;
		(basic_block_table[basic_block.getName()])->in.clear();
		for (itv=vresult1.begin();itv!=vresult1.end();++itv)
		{
			(basic_block_table[basic_block.getName()])->in.insert(*itv);
			//llvm::errs() <<"itv"<<*itv<<'\n';
		}
		}
		llvm::errs() << " }\n";
		PrintSeti((basic_block_table[basic_block.getName()])->in);
		// Traverse successors
		llvm::errs() << " Successors: {";
		for (llvm::succ_iterator it = succ_begin(&basic_block),
		e = llvm::succ_end(&basic_block);
		it != e;
		++it)
		{
		llvm::BasicBlock *succ = *it;
		llvm::errs() << ' ' << succ->getName();
		}
		llvm::errs() << " }\n";
		// Traverse instructions
		ig=0;
		for (llvm::BasicBlock::iterator instruction = basic_block.begin(),
		e = basic_block.end();
		instruction != e;
		++instruction)
		{
			ig++;
		}
		ng=ig;
		ig=0;
		for (llvm::BasicBlock::iterator instruction = basic_block.begin(),
		e = basic_block.end();
		instruction != e;
		++instruction,++ig)
		{
		if(ig<ng-1)
		{
			expi=instruction->getName();
			exp=instruction->getOpcodeName();
			if(exp!="alloca"&&exp!="store")
			{
			for (unsigned i1 = 0; i1 < (instruction->getNumOperands()); i1++)
			{
			llvm::Value *arg = instruction->getOperand(i1);
			exp1=(arg->getName());
				if(exp1=="")
				{
					llvm::ConstantInt* I=llvm::dyn_cast<llvm::ConstantInt>(arg);
					int ss1=I->getSExtValue();
					exp1=std::to_string(ss1);
				}
			exp=exp+exp1;
			}
			std::string d2= instruction->getOpcodeName();
			if(d2!="store")
			{
			//exp=expi+"="+exp;
			}
			Instruction_table[instruction->getName()]->insetg.insert(exp);
			(basic_block_table[basic_block.getName()])->gen.insert(exp);
			}
		}
		
		}
		seti=((basic_block_table[basic_block.getName()])->in);
		setg=((basic_block_table[basic_block.getName()])->gen);
		seto=((basic_block_table[basic_block.getName()])->out);
		(ExtendSet(seti,setg));
		(basic_block_table[basic_block.getName()])->out=seti;
		if(seto!=((basic_block_table[basic_block.getName()])->out))
		{
			check3=check3+1;
		}
		PrintSetg((basic_block_table[basic_block.getName()])->gen);
		PrintSeto((basic_block_table[basic_block.getName()])->out);
		llvm::errs()<<"-----"<<"\n";
	}

	std::vector<std::string> instersection(std::vector<std::string> &v1, std::vector<std::string> &v2)
	{

		std::vector<std::string> v3;

		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());

		set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));

		return v3;
	}
	
};
class CSE : public llvm::FunctionPass
{
	std::set<std::string> st;
	public:
		static char ID;
	// Constructor. The first argument of the parent constructor is
	// a unique pass identifier.
	CSE() : llvm::FunctionPass(ID) { }
	// Virtual function overridden to implement the pass functionality.
		std::vector<llvm::Instruction*> rpins;
		std::vector<llvm::Instruction*> rmins;
	bool runOnFunction(llvm::Function &function) override
	{
		// Print function name
		llvm::errs() << "Transform Pass on function: " << function.getName() << " Common Subexpression Elimination" <<'\n';
		for (llvm::Function::iterator basic_block = function.begin(),
		e = function.end();
		basic_block != e;
		++basic_block)
		{
			   llvm::errs() << basic_block->getName() << " :" <<'\n';
			for(llvm::BasicBlock::iterator ins=basic_block->begin(),e=basic_block->end();
				ins!=e;++ins)
			{
				llvm::BasicBlock::iterator stop=ins;
				stop++;
				llvm::BasicBlock::iterator stit;
				if(stop!=basic_block->end())
				{
					dset.clear();
					llvm::BasicBlock::iterator p=ins;
					p--;
					llvm::errs()<<"-------------------"<<'\n';
					//llvm::errs()<<ins->getName()<<'\n';
					ins->dump();
					llvm::errs()<<'\n';
					if(ins!=basic_block->begin())
					{
					Instruction_table[ins->getName()]->inseti=Instruction_table[p->getName()]->inseto;
					}
					else
					{
						Instruction_table[ins->getName()]->inseti=basic_block_table[basic_block->getName()]->in;
					}
		
					std::string cmps=ins->getOpcodeName();
					if(cmps!="store")
					PrintSeti(Instruction_table[ins->getName()]->inseti);
					ExtendSet(dset,Instruction_table[ins->getName()]->insetg);
					ExtendSet(dset,Instruction_table[ins->getName()]->inseti);
					Instruction_table[ins->getName()]->inseto=dset;
					if(cmps!="store")
					{
					PrintSetg(Instruction_table[ins->getName()]->insetg);
					
					
					PrintSeto(Instruction_table[ins->getName()]->inseto);
					}
				}
				
			}
				
		}
		llvm::errs()<<"-------------------"<<'\n';
		std::map<std::string,Instruction*>::iterator itm;
			std::map<std::string,Instruction*>::iterator itmc;
			std::set<std::string>::iterator its1;
			std::string expression="";
			std::string expression1="";
			int c_str=0;
			std::string inst_name;
			int c=0;int c1=0;
			//llvm::BasicBlock iterator insf;
			for(itm=Instruction_table.begin();itm!=Instruction_table.end();++itm)
			{
				for(its1=itm->second->insetg.begin();its1!=itm->second->insetg.end();++its1)
				{
					if(itm->second->inseti.find(*its1)!=itm->second->inseti.end())
					{
						for (llvm::Function::iterator basic_block = function.begin(),e = function.end();basic_block != e;++basic_block)
						{
							for(llvm::BasicBlock::iterator ins2=basic_block->begin();ins2!=basic_block->end();++ins2)
							{
								inst_name=ins2->getName();
								//llvm::errs()<<ins2->getName();
								if(inst_name==itm->first)
								{
									llvm::errs()<<"CSE:"<<'\n';
									llvm::errs()<<"Removed Instruction:";
									ins2->dump();
									 rmins.push_back(ins2);
								//	c++;
									//llvm::errs()<<c<<"\n";
								}
							}
						}
					 	//llvm::errs()<<"removed instruction:"<<itm->first<<"="<<*its1<<"==>";
						std::string rm=itm->first;
						for (llvm::Function::iterator basic_block1 = function.begin(),e = function.end();basic_block1 != e;++basic_block1)
						{
							for(llvm::BasicBlock::iterator ins1=basic_block1->begin();ins1!=basic_block1->end();++ins1)
							{
								expression=ins1->getOpcodeName();
								for(unsigned i=0;i<(ins1->getNumOperands());i++)
								{
									llvm::Value *arg = ins1->getOperand(i);
									expression1=(arg->getName());
									if(expression1=="")
									{
										llvm::ConstantInt* I=llvm::dyn_cast<llvm::ConstantInt>(arg);
										int ss1=I->getSExtValue();
										expression1=std::to_string(ss1);
									}
									expression=expression+expression1;
									//llvm::ReplaceInstWithInst(ins2,ins1);
								}
								std::string check_str=*its1;
								c_str=0;
								if(expression==check_str)
								{
									llvm::errs()<<"Replaced With:";
									ins1->dump();
									rpins.push_back(ins1);
									/*llvm::errs()<<"**********"<<'\n';
									rmins[c1]->dump();
									rpins[c1]->dump();
									c1++;
									llvm::errs()<<"**********"<<'\n';*/
									//llvm::errs()<<c1<<"\n";
									llvm::errs()<<"-------------------"<<'\n';
									
									
									c_str=1;
									break;
								}
								if(c_str)
								{
									break;
								}
							}
							 if(c_str)
							{
								break;
							}
						}
					}
				}
			}
			for(int re=0;re<rmins.size();re++)
			{
				//rmins[re]->dump();
				//rpins[re]->dump();
				
				rmins[re]->replaceAllUsesWith(rpins[re]);  //***//
		
				rmins[re]->getParent()->getInstList().erase(rmins[re]);	//***//
			}
			
	}

};


// Pass identifier
char PrintPass::ID = 0;
// Pass registration. Pass will be available as 'print' from the LLVM
// optimizer tool.
static llvm::RegisterPass<PrintPass> X("avexp",
"My function pass",
false,
false);
char CSE::ID = 0;
static llvm::RegisterPass<CSE> X1("cse",
"My function pass",
false,
false);
}
