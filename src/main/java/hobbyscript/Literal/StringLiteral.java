package hobbyscript.Literal;

import hobbyscript.Ast.AstLeaf;
import hobbyscript.Compile.CodeLine;
import hobbyscript.Eval.Env.EnvironmentCallBack;
import hobbyscript.Eval.ScriptEval;
import hobbyscript.Token.HobbyToken;

/**
 * String
 * Created by liufengkai on 16/7/12.
 */
public class StringLiteral extends AstLeaf {
    public StringLiteral(HobbyToken token) {
        super(token);
    }

    public String value() {
        return token.getText();
    }

    @Override
    public String compile(CodeLine line, int th, int nx) {
        return token.getText();
    }

    @Override
    public Object eval(EnvironmentCallBack env) {
        return ScriptEval.StringEval(this);
    }
}
